GEOSTAR_HOME=/home/yate/geostar


SIMPLEFEATURES_INCLUDES=-I${GEOSTAR_HOME}/libraries/simpleFeatures/src

GAIA_INCLUDES=-I${GEOSTAR_HOME}/libraries/gaia-gis/installdir/include \
		-I${GEOSTAR_HOME}/libraries/gaia-gis/libspatialite/src/headers
GAIA_LIBRARIES=-L${GEOSTAR_HOME}/libraries/gaia-gis/installdir/lib \
	-lspatialite -lproj -lsqlite3 -lfreexl -lgeos -lgeos_c -lopenjp2

BOOST_INCLUDES=-I${GEOSTAR_HOME}/libraries/boost_1_65_0
BOOST_LIBRARIES=${GEOSTAR_HOME}/libraries/boost_1_65_0/stage/lib/libboost_filesystem.a \
		${GEOSTAR_HOME}/libraries/boost_1_65_0/stage/lib/libboost_system.a

EIGEN_INCLUDES=-I${GEOSTAR_HOME}/libraries/eigen-eigen-5a0156e40feb
##EIGEN_LIBRARIES=../eigen-eigen-5a0156e40feb/stage/lib/libboost_filesystem.a \
##	../boost_1_63_0/stage/lib/libboost_system.a

##HDF5_INCLUDES=-I${GEOSTAR_HOME}/libraries/hdf5-1.10.1/c++/src  \
##	      -I${GEOSTAR_HOME}/libraries/hdf5-1.10.1/hdf5/include
##HDF5_LIBRARIES=${GEOSTAR_HOME}/libraries/hdf5-1.10.1/lib/libhdf5_cpp.a \
##	       ${GEOSTAR_HOME}/libraries/hdf5-1.10.1/lib/libhdf5.a -lz -ldl -lm

HDF5_INCLUDES=-I${GEOSTAR_HOME}/libraries/hdf5-1.10.0-patch1/include
HDF5_LIBRARIES=${GEOSTAR_HOME}/libraries/hdf5-1.10.0-patch1/lib/libhdf5_cpp.a \
	       ${GEOSTAR_HOME}/libraries/hdf5-1.10.0-patch1/lib/libhdf5.a -lz -ldl -lm

GDAL_INCLUDES=-I${GEOSTAR_HOME}/libraries/gdal-2.3.0/include
##GDAL_LIBRARIES=../gdal-2.1.3/lib/libgdal.a -lfreexl -L/usr/local/lib -lgeos_c  -lsqlite3 -lodbc -lodbcinst -lexpat -lxerces-c -lpthread -ljasper -lnetcdf -L../hdf5-1.10.0-patch1/lib -lhdf5  -logdi -lgif -ljpeg -lpng -lcfitsio -L/usr/lib -lpq -lz -lpthread -lm -lrt -ldl -lcurl -lxml2
GDAL_LIBRARIES=-L${GEOSTAR_HOME}/libraries/gaia-gis/proj-4.9.2/lib -lproj \
	       -L${GEOSTAR_HOME}/libraries/gdal-2.3.0/lib -lgdal \
               -L${GEOSTAR_HOME}/libraries/freexl-1.0.2/lib -lfreexl \
	       -L${GEOSTAR_HOME}/libraries/geos-3.5.0/lib -lgeos_c -L/usr/local/lib \
	       -L${GEOSTAR_HOME}/libraries/gaia-gis/installdir/lib \
	       -lsqlite3 -lodbc -lodbcinst -lexpat -lxerces-c \
	       -lpthread -ljasper -lnetcdf -logdi -lgif -ljpeg -lpng \
               -lcfitsio -L/usr/lib -lpq -lz -lpthread -lm -ldl -lcurl -lxml2
## -liconv

IFILE_INCLUDES=-I${GEOSTAR_HOME}/libraries/ifile_cpplib
IFILE_LIBRARIES=${GEOSTAR_HOME}/libraries/ifile_cpplib/IFile.o \
	${GEOSTAR_HOME}/libraries/ifile_cpplib/hdf5vfs_cpp.o

SQLCPP_INCLUDES=-I${GEOSTAR_HOME}/libraries/libsqlitecpp/include
SQLCPP_LIBRARIES=-L${GEOSTAR_HOME}/libraries/libsqlitecpp/lib -lsqlitecpp

SPATIALITECPP_INCLUDES=-I${GEOSTAR_HOME}/libraries/libspatialitecpp/include
SPATIALITECPP_LIBRARIES=-L${GEOSTAR_HOME}/libraries/libspatialitecpp/lib -lspatialitecpp


FFTW_INCLUDES=-I${GEOSTAR_HOME}/libraries/fftw-3.3.7/include
FFTW_LIBRARIES=-L${GEOSTAR_HOME}/libraries/fftw-3.3.7/lib -lfftw3

CAIRO_INCLUDES=-I${GEOSTAR_HOME}/libraries/cairo-1.14.12/include/cairo
CAIRO_LIBRARIES=-L${GEOSTAR_HOME}/libraries/cairo-1.14.12/lib -lcairo

CAIROMM_INCLUDES=-I${GEOSTAR_HOME}/libraries/cairomm-1.12.2/include/cairomm-1.0
CAIROMM_LIBRARIES=-L${GEOSTAR_HOME}/libraries/cairomm-1.12.2/lib -lcairomm-1.0

SIGPP_INCLUDES=-I${GEOSTAR_HOME}/libraries/libsigc++-2.10.0/include/sigc++-2.0
SIGPP_LIBRARIES=-L${GEOSTAR_HOME}/libraries/libsigc++-2.10.0/lib -lsigc-2.0

FREETYPE_INCLUDES=-I/usr/include/freetype2

PLPLOT_INCLUDES=-I${GEOSTAR_HOME}/libraries/plplot-5.13.0/build_dir/include/plplot
PLPLOT_LIBRARIES=-L${GEOSTAR_HOME}/libraries/plplot-5.13.0/build_dir/lib -lplplot -lplplotcxx




INCL=${BOOST_INCLUDES} ${EIGEN_INCLUDES} ${HDF5_INCLUDES} ${GDAL_INCLUDES} \
      ${GAIA_INCLUDES} ${SQLCPP_INCLUDES} \
	${FFTW_INCLUDES} ${IFILE_INCLUDES} \
	${SPATIALITECPP_INCLUDES} \
	-I${GEOSTAR_HOME}/src ${CAIRO_INCLUDES} ${CAIROMM_INCLUDES} \
	${SIGPP_INCLUDES} ${FREETYPE_INCLUDES} ${PLPLOT_INCLUDES} \
	${SIMPLEFEATURES_INCLUDES}

LIBS=${BOOST_LIBRARIES} ${HDF5_LIBRARIES} ${GDAL_LIBRARIES} \
      ${SQLCPP_LIBRARIES}  ${GAIA_LIBRARIES} \
	${FFTW_LIBRARIES} \
	${SPATIALITECPP_LIBRARIES} \
	${CAIRO_LIBRARIES} ${CAIROMM_LIBRARIES} \
	${SIGPP_LIBRARIES} ${PLPLOT_LIBRARIES}

WARN=-pedantic -Wall -Wextra -Wcast-align -Wcast-qual -Wctor-dtor-privacy -Wdisabled-optimization -Wformat=2 -Winit-self -Wlogical-op -Wmissing-declarations -Wmissing-include-dirs -Wnoexcept -Wold-style-cast -Woverloaded-virtual -Wredundant-decls -Wshadow -Wsign-conversion -Wsign-promo -Wstrict-null-sentinel -Wstrict-overflow=5 -Wswitch-default -Wundef -Werror -Wno-unused

##STD=-std=c++0x
STD=-std=c++11

DEBUG=-g

CPPDEBUG=-DDEBUG

CPPFLAGS=-DSPATIALITECPP_PTRTYPE=4

clean:
	/bin/rm -f *.o test_ifile test_sql testcppvector test3


attributes.o: attributes.cpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o attributes.o attributes.cpp ${INCL}

File.o: File.cpp File.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o File.o File.cpp ${INCL}

Image.o: Image.cpp Image.hpp File.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Image.o Image.cpp ${INCL}

Raster.o: Raster.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp WarpParameters.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster.o Raster.cpp ${INCL}

Raster_bitmap.o: Raster_bitmap.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp WarpParameters.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster_bitmap.o Raster_bitmap.cpp ${INCL}

Raster_flip.o: Raster_flip.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp WarpParameters.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster_flip.o Raster_flip.cpp ${INCL}

Raster_histogram.o: Raster_histogram.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp WarpParameters.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster_histogram.o Raster_histogram.cpp ${INCL}

Raster_minmax.o: Raster_minmax.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp WarpParameters.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster_minmax.o Raster_minmax.cpp ${INCL}

Raster_polygon.o: Raster_polygon.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp Polygon.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster_polygon.o Raster_polygon.cpp ${INCL}

Raster_reproject.o: Raster_reproject.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp WarpParameters.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster_reproject.o Raster_reproject.cpp ${INCL}

Raster_rotate.o: Raster_rotate.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp WarpParameters.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster_rotate.o Raster_rotate.cpp ${INCL}

Raster_scale.o: Raster_scale.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp WarpParameters.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster_scale.o Raster_scale.cpp ${INCL}

Raster_set.o: Raster_set.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp WarpParameters.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster_set.o Raster_set.cpp ${INCL}

Raster_warp.o: Raster_warp.cpp Raster.hpp RasterType.hpp Image.hpp Slice.hpp WarpParameters.hpp TileIO.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Raster_warp.o Raster_warp.cpp ${INCL}

Slice.o: Slice.cpp Slice.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Slice.o Slice.cpp ${INCL}

WarpParameters.o: WarpParameters.cpp WarpParameters.hpp Point.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o WarpParameters.o WarpParameters.cpp ${INCL}

TileIO.o: TileIO.cpp TileIO.hpp Point.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o TileIO.o TileIO.cpp ${INCL}

rasterpolygonenumerator.o: rasterpolygonenumerator.cpp polygonize.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o rasterpolygonenumerator.o rasterpolygonenumerator.cpp ${INCL}

polygonize.o: polygonize.cpp polygonize.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o polygonize.o polygonize.cpp ${INCL}


Vector.o: Vector.cpp Vector.hpp Shape.hpp File.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Vector.o Vector.cpp ${INCL}

Shape.o: Shape.cpp Shape.hpp File.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Shape.o Shape.cpp ${INCL}


obj_object.o: obj_object.cpp obj_object.hpp File.hpp Exceptions.hpp attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o obj_object.o obj_object.cpp ${INCL} #${CPPDEBUG}



##Ifile.o: Ifile.cpp File.hpp Exceptions.hpp attributes.hpp
##	g++ ${DEBUG} ${STD} ${CPPFLAGS} -c -o Ifile.o Ifile.cpp ${INCL}

test_main: test_main.cpp obj_object.o obj_object.hpp File.o Exceptions.hpp attributes.o attributes.hpp
	g++ ${DEBUG} ${STD} ${CPPFLAGS} -o test_main test_main.cpp File.o \
	       attributes.o obj_object.o -I${GEOSTAR_HOME}/src \
	     ${INCL} ${IFILE_LIBRARIES} ${LIBS} ${LIBS}

test: test_main
	rm obj_object.o
	rm ./test.h5
	./test_main

## REMOVED -lrt from GDAL_LIBS   !!!!!!!!!!!!!!!!!!!
## had to do:
## ./configure --prefix=`pwd` --with-df5=/home/lep/MDP2/codes/demo9/hdf5-1.10.0-patch1 --without-hdf4
## export LD_LIBRARY_PATH=/home/lep/MDP2/codes/demo9/hdf5-1.10.0-patch1/lib
GDAL_EXTRAS=-L../freexl-1.0.2/lib -L../geos-3.6.1/lib -L../unixODBC-2.3.4/lib -L../xerces-c-3.1.4/lib -L../jasper-2.0.12/mybuild/lib -L../netcdf-4.4.1.1/lib -L../ogdi-3.2.0/lib/ogdi -L../giflib-5.1.4/lib -L../jpeg-9b/lib -L../libpng-1.6.29/lib -L../cfitsio/lib
GDAL_LIBS=-lfreexl -L/usr/local/lib -lgeos_c  -lsqlite3 -lodbc -lodbcinst -lexpat -lxerces-c -lpthread -ljasper -lnetcdf -L../hdf5-1.10.0-patch1/lib -lhdf5  -logdi -lgif -ljpeg -lpng -lcfitsio -L/usr/lib -lpq -lz -lpthread -lm -ldl -lcurl -lxml2 -liconv
# NEW HERE:
aINCL = ${BOOST_INCLUDES} ${HDF5_INCLUDES} ${GDAL_INCLUDES}
aLIBS = ${BOOST_LIBRARIES} ${HDF5_LIBRARIES} ${GDAL_LIBRARIES} ${GDAL_EXTRAS} ${GDAL_LIBS}


