//________________________________________________
#include <stdio.h>
#include <math.h>
#include "MarchingCubes.h"
#include "defs.h"
#include "fparser.h"

char* isofilename;
char *finalmeshname;

//_____________________________________________________________________________
// main marching cubes object
MarchingCubes mc ;

// isovalue defining the isosurface
float isoval = 0.0f ;

// original/topological MC switch
int   originalMC = 0 ;

// grid extension
float xmin=-1.0f, xmax=1.0f,  ymin=-1.0f, ymax=1.0f,  zmin=-1.0f, zmax=1.0f ;
// grid size control
int   size_x=50, size_y=50, size_z=50 ;

// loaded iso grid
FILE  *isofile  ;

// implicit formula
char  *formula;

// switch to export iso grid
int  export_iso = 0 ;

enum Axis      { X=0, Y=1, Z=2 };

//_____________________________________________________________________________

void reading_data()
{
	unsigned char buf[sizeof(float)];
	fread(buf, sizeof(float), 1, isofile);
	size_x = *(int*) buf;
	fread(buf, sizeof(float), 1, isofile);
	size_y = *(int*) buf;
	fread(buf, sizeof(float), 1, isofile);
	size_z = *(int*) buf;

	fread(buf, sizeof(float), 1, isofile);
	xmin = *(float*) buf;
	fread(buf, sizeof(float), 1, isofile);
	xmax = *(float*) buf;
	fread(buf, sizeof(float), 1, isofile);
	ymin = *(float*) buf;
	fread(buf, sizeof(float), 1, isofile);
	ymax = *(float*) buf;
	fread(buf, sizeof(float), 1, isofile);
	zmin = *(float*) buf;
	fread(buf, sizeof(float), 1, isofile);
	zmax = *(float*) buf;
	formula = "i-0";
}

//_____________________________________________________________________________
// run the MC algorithm
bool run()
//-----------------------------------------------------------------------------
{
  // Init data
  mc.clean_all() ;
  mc.set_resolution( size_x, size_y, size_z ) ;
  mc.init_all() ;

  // Parse formula
  FunctionParser fparser ;
  fparser.Parse( (const char*)formula, "x,y,z,c,i" ) ;
  if( fparser.EvalError() )
  {
    printf( "parse error\n" ) ;
    return false ;
  }

  // Fills data structure
  int i,j,k ;
  float val[5], w ;
  float rx = (xmax-xmin) / (size_x - 1) ;
  float ry = (ymax-ymin) / (size_y - 1) ;
  float rz = (zmax-zmin) / (size_z - 1) ;
  unsigned char buf[sizeof(float)] ;
  for( i = 0 ; i < size_x ; i++ )
  {
    val[X] = (float)i * rx  + xmin ;
    for( j = 0 ; j < size_y ; j++ )
    {
      val[Y] = (float)j * ry  + ymin ;
      for( k = 0 ; k < size_z ; k++ )
      {
        val[Z] = (float)k * rz  + zmin ;

        if( isofile  )
        {
          fread (buf, sizeof(float), 1, isofile);
          val[4] = * (float*) buf ;
        }
        w = fparser.Eval(val) - isoval ;
        mc.set_data( w, i,j,k ) ;
      }
    }
  }
  if( export_iso ) mc.writeISO( finalmeshname) ;

  // Run MC
  mc.run() ;
  mc.clean_temps() ;

  // Rescale positions
  for( i = 0 ; i < mc.nverts() ; ++i )
  {
    Vertex &v = mc.vertices()[i] ;
    v.x = rx * v.x + xmin ;
    v.y = ry * v.y + xmin ;
    v.z = rz * v.z + ymin ;
    float nrm = v.nx * v.nx + v.ny * v.ny + v.nz * v.nz ;
    if( nrm != 0 )
    {
      nrm = 1.0 / sqrt(nrm) ;
      v.nx *= nrm ;
      v.ny *= nrm ;
      v.nz *= nrm ;
    }
  }

  if( isofile )
  {
    rewind( isofile ) ;
    fread (buf, sizeof(float), 1, isofile);
    fread (buf, sizeof(float), 1, isofile);
    fread (buf, sizeof(float), 1, isofile);
    fread (buf, sizeof(float), 1, isofile);
    fread (buf, sizeof(float), 1, isofile);
    fread (buf, sizeof(float), 1, isofile);
    fread (buf, sizeof(float), 1, isofile);
    fread (buf, sizeof(float), 1, isofile);
    fread (buf, sizeof(float), 1, isofile);
  }

  return true ;
}


//_____________________________________________________________________________
// main function
int main(int argc, char* argv[])
//-----------------------------------------------------------------------------
	{

	printf("Correct Marching Cubes 33:\n");

	  if(argc != 4)
	    {
	    std::cout << "Usage: " << argv[0] << "Filename(.iso) isoval (float) MeshName(.ply)" << std::endl;
	    return 1;
	    }

	isofilename    = argv[1];
	isoval = atof(argv[2]);
	finalmeshname  = argv[3];

	// reading the isofile
	printf("Correct Marching Cubes 33: Reading input file.\n");
	isofile = fopen(isofilename, "rb");

	if (!isofile)
	{
		printf("Correct Marching Cubes 33: problem in reading file.\n");
		return 1;
	}
	reading_data();
	run();
	mc.writePLY(finalmeshname);
	mc.clean_all();

return 0;
}



