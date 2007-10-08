//
// $Id$
//
/*!
  \file
  \ingroup projection

  \brief non-inline implementations for ProjectorByBinPairUsingProjMatrixByBin
  
  \author Kris Thielemans
    
  $Date$
  $Revision$
*/
/*
    Copyright (C) 2000- $Date$, Hammersmith Imanet Ltd
    See STIR/LICENSE.txt for details
*/


#include "stir/recon_buildblock/ProjectorByBinPairUsingProjMatrixByBin.h"
#include "stir/recon_buildblock/ForwardProjectorByBinUsingProjMatrixByBin.h"
#include "stir/recon_buildblock/BackProjectorByBinUsingProjMatrixByBin.h"
#include "stir/is_null_ptr.h"
#include "stir/Succeeded.h"

START_NAMESPACE_STIR


const char * const 
ProjectorByBinPairUsingProjMatrixByBin::registered_name =
  "Matrix";


void 
ProjectorByBinPairUsingProjMatrixByBin::initialise_keymap()
{
  base_type::initialise_keymap();
  parser.add_start_key("Projector Pair Using Matrix Parameters");
  parser.add_stop_key("End Projector Pair Using Matrix Parameters");
  parser.add_parsing_key("Matrix type",&proj_matrix_sptr);
}


void
ProjectorByBinPairUsingProjMatrixByBin::set_defaults()
{
  base_type::set_defaults();
  proj_matrix_sptr = 0;
}

bool
ProjectorByBinPairUsingProjMatrixByBin::post_processing()
{
  if (base_type::post_processing())
    return true;
  if (is_null_ptr(proj_matrix_sptr))
    { warning("No valid projection matrix is defined\n"); return true; }
  forward_projector_sptr = new ForwardProjectorByBinUsingProjMatrixByBin(proj_matrix_sptr);
  back_projector_sptr = new BackProjectorByBinUsingProjMatrixByBin(proj_matrix_sptr);
  return false;
}

ProjectorByBinPairUsingProjMatrixByBin::
ProjectorByBinPairUsingProjMatrixByBin()
{
  set_defaults();
}

ProjectorByBinPairUsingProjMatrixByBin::
ProjectorByBinPairUsingProjMatrixByBin(  
    const shared_ptr<ProjMatrixByBin>& proj_matrix_sptr)	   
    : proj_matrix_sptr(proj_matrix_sptr)
{}

#if 0
// not needed as the projection matrix will be set_up indirectly by
// the forward_projector->set_up (which is calle in the base class)
Succeeded
ProjectorByBinPairUsingProjMatrixByBin::
set_up(const shared_ptr<ProjDataInfo>& proj_data_info_sptr,
       const shared_ptr<DiscretisedDensity<3,float> >& image_info_sptr)
{    	 

  // TODO use return value
  proj_matrix_sptr->set_up(proj_data_info_sptr, image_info_sptr);

  if (base_type::set_up(target_sptr) != Succeeded::yes)
    return Succeeded::no;

  return Succeeded::yes;
}
#endif

ProjMatrixByBin const * 
ProjectorByBinPairUsingProjMatrixByBin::
get_proj_matrix_ptr() const
{
  return proj_matrix_sptr.get();
}

END_NAMESPACE_STIR
