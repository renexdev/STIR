//
// $Id$
//
/*!

  \file

  \brief Implementation of class PostsmoothingBackProjectorByBin

  \author Kris Thielemans

  $Date$
  $Revision$
*/
/*
    Copyright (C) 2000- $Date$, HammersmithImanet
    See STIR/LICENSE.txt for details
*/

#include "local/stir/recon_buildblock/PostsmoothingBackProjectorByBin.h"
#include "stir/DataProcessor.h"
#include "stir/DiscretisedDensity.h"

START_NAMESPACE_STIR
const char * const 
PostsmoothingBackProjectorByBin::registered_name =
  "Post Smoothing";


void
PostsmoothingBackProjectorByBin::
set_defaults()
{
  original_back_projector_ptr = 0;
  image_processor_ptr = 0;
}

void
PostsmoothingBackProjectorByBin::
initialise_keymap()
{
  parser.add_start_key("Post Smoothing Back Projector Parameters");
  parser.add_stop_key("End Post Smoothing Back Projector Parameters");
  parser.add_parsing_key("Original Back projector type", &original_back_projector_ptr);
  parser.add_parsing_key("filter type", &image_processor_ptr);
}

bool
PostsmoothingBackProjectorByBin::
post_processing()
{
  if (original_back_projector_ptr.use_count() == 0)
  {
    warning("Pre Smoothing Back Projector: original back projector needs to be set\n");
    return true;
  }
  return false;
}

PostsmoothingBackProjectorByBin::
  PostsmoothingBackProjectorByBin()
{
  set_defaults();
}

PostsmoothingBackProjectorByBin::
PostsmoothingBackProjectorByBin(
                       const shared_ptr<BackProjectorByBin>& original_back_projector_ptr,
		       const shared_ptr<DataProcessor<DiscretisedDensity<3,float> > >& image_processor_ptr)
                       : original_back_projector_ptr(original_back_projector_ptr),
			 image_processor_ptr(image_processor_ptr)
{}

PostsmoothingBackProjectorByBin::
~PostsmoothingBackProjectorByBin()
{}

void
PostsmoothingBackProjectorByBin::
set_up(const shared_ptr<ProjDataInfo>& proj_data_info_ptr,
       const shared_ptr<DiscretisedDensity<3,float> >& image_info_ptr)
{
  original_back_projector_ptr->set_up(proj_data_info_ptr, image_info_ptr);
  // don't do set_up as image sizes might change
  //if (image_processor_ptr.use_count()!=0)
  //   image_processor_ptr->set_up(*image_info_ptr);
}

const DataSymmetriesForViewSegmentNumbers * 
PostsmoothingBackProjectorByBin::
get_symmetries_used() const
{
  return original_back_projector_ptr->get_symmetries_used();
}

void 
PostsmoothingBackProjectorByBin::
actual_back_project(DiscretisedDensity<3,float>& density,
		    const RelatedViewgrams<float>& viewgrams, 
		    const int min_axial_pos_num, const int max_axial_pos_num,
		    const int min_tangential_pos_num, const int max_tangential_pos_num)
{
  if (image_processor_ptr.use_count()!=0)
    {
      shared_ptr<DiscretisedDensity<3,float> > filtered_density_ptr = 
	density.get_empty_discretised_density();
      assert(density.get_index_range() == filtered_density_ptr->get_index_range());
      original_back_projector_ptr->back_project(*filtered_density_ptr, viewgrams, 
						min_axial_pos_num, max_axial_pos_num,
						min_tangential_pos_num, max_tangential_pos_num);
      image_processor_ptr->apply(*filtered_density_ptr);
      density += *filtered_density_ptr;
    }
  else
    {
      original_back_projector_ptr->back_project(density, viewgrams, 
						min_axial_pos_num, max_axial_pos_num,
						min_tangential_pos_num, max_tangential_pos_num);
    }
}
 


END_NAMESPACE_STIR
