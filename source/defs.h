/**
 * @file    glui_defs.h
 * @author  Thomas Lewiner <thomas.lewiner@polytechnique.org>
 * @author  Math Dept, PUC-Rio
 * @version 0.3
 * @date    30/05/2006
 *
 * @brief   MarchingCubes Graphical interface
 */
//________________________________________________


#ifndef _MC_GLUI_DEFS_H_
#define _MC_GLUI_DEFS_H_

#if !defined(WIN32) || defined(__CYGWIN__)
#pragma interface
#endif // WIN32


//#include <GL/glui.h> // openGL user interface
#include <stdio.h>   // i/o functions
#include "MarchingCubes.h"


#ifdef _DEBUG
#define PRINT_GL_DEBUG  { if( ::glGetError() != GL_NO_ERROR ) printf( "openGL watch at line %d: %s\n", __LINE__, ::gluErrorString( ::glGetError() ) ) ; }
#else  // _DEBUG
#define PRINT_GL_DEBUG  {}
#endif // _DEBUG


//_____________________________________________________________________________
// Marching Cubes component

  /// main marching cubes object
  extern MarchingCubes mc ;

  /// isovalue defining the isosurface
  extern float isoval ;

  /// original/topological MC switch
  extern int   originalMC ;

  /// grid left extension
  extern float xmin ;
  /// grid right extension
  extern float xmax ;
  /// grid near extension
  extern float ymin ;
  /// grid far extension
  extern float ymax ;
  /// grid bottom extension
  extern float zmin ;
  /// grid up extension
  extern float zmax ;

  /// grid horizontal size control
  extern int size_x ;
  /// grid depth size control
  extern int size_y ;
  /// grid vertical size control
  extern int size_z ;


  //-----------------------------------------------------------------------------
// input data

  /// implicit formula
  extern char  *formula ;

  /// number of example implicit functions
  #define NFUNS 15
  /// implicit functions
  extern char *fun_list[NFUNS] ;
  /// implicit functions
  extern char *fun_def [NFUNS] ;
  /// chosen implicit function
  extern int   curr_string ;

  /// cube data
  extern float v[8] ;

  /// loaded iso grid
  extern FILE        *isofile  ;

//-----------------------------------------------------------------------------
// main functions

/// run the MC algorithm
bool run() ;

/// Command Line
bool parse_cmdline( int argc, char* argv[] ) ;


//-----------------------------------------------------------------------------
// I/O functions

  /// switch to export iso grid
  extern int  export_iso ;

/// set file extension of out_filename
int  set_ext( const char ext[3] ) ;

/// EPS export
void export_eps() ;

/// PPM export
void export_ppm() ;

/// TGA export
void export_tga() ;

//_____________________________________________________________________________


#endif // _MC_GLUI_DEFS_H_
