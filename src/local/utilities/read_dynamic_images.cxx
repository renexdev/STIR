//
// $Id$
//
/*
    Copyright (C) 2005- $Date$, Hammersmith Imanet Ltd
    This file is part of STIR.

    This file is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.

    This file is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    See STIR/LICENSE.txt for details
*/
/*!
  \file
  \ingroup utilities
  \brief Reading Dynamic Images
  \author Charalampos Tsoumpas
  
  This program reads dynamic images given from a file. 

  \par Usage:
  \code 
  read_dynamic_images input_dynamic_image_in_ECAT7_format
  \endcode
  
  \warning At the moment this method works only for images stored in ECAT7 format.
  \sa DynamicDiscretisedDensity.h class

  $Date$
  $Revision$
  
*/

#include "stir/IO/read_data_1d.h"
#include "stir/IO/read_data.h"
#include "stir/Array.h"
#include "local/stir/DynamicDiscretisedDensity.h"
#include <cstring>
#include <iostream>

int main(int argc, char *argv[])
{ 
  USING_NAMESPACE_STIR
  
  if (argc<2 || argc>2)
    {
      std::cerr << "Usage:" << argv[0] << "\n"
	   << "\t[dynamic_image_filename]\n";
      return EXIT_FAILURE;            
    }       

  shared_ptr< DynamicDiscretisedDensity >  dyn_image_sptr= 
  DynamicDiscretisedDensity::read_from_file(argv[1]); // The written image is read in respect to its center as origin!!!
  const DynamicDiscretisedDensity & dyn_image = *dyn_image_sptr;
  std::cerr << "DynamicDiscretisedDensity is read OK." << " \n "
	    << "Calibration Factor is: " << dyn_image.get_calibration_factor() << "\n" 
	    << "Isotope Halflife is: " << dyn_image.get_isotope_halflife() << "\n\n" ;

  return EXIT_SUCCESS;
}

