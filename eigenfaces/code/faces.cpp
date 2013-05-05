
/////////////////////////////////////////////////////////////////////////////////////////////////
//	Project 4: Eigenfaces                                                                      //
//  CSE 455 Winter 2003                                                                        //
//	Copyright (c) 2003 University of Washington Department of Computer Science and Engineering //
//                                                                                             //
//  File: faces.cpp                                                                            //
//	Author: David Laurence Dewey                                                               //
//	Contact: ddewey@cs.washington.edu                                                          //
//           http://www.cs.washington.edu/homes/ddewey/                                        //
//                                                                                             //
/////////////////////////////////////////////////////////////////////////////////////////////////



#include "stdafx.h"

#include "jacob.h"

Faces::Faces()
:
Array<Face>(),
width(0),
height(0),
vector_size(0)
{
	//empty
}

Faces::Faces(int count, int width, int height)
:
Array<Face>(count),
width(width),
height(height),
vector_size(width*height)
{
	for (int i=0; i<getSize(); i++) {
		(*this)[i].resize(width, height, 1);
	}
}

void Faces::load(BinaryFileReader& file)
{
	resize(file.readInt());
	width=file.readInt();
	height=file.readInt();
	vector_size=width*height;
	for (int i=0; i<getSize(); i++) {
		(*this)[i].load(file);
	}
	average_face.load(file);
	std::cout << "Loaded faces from '" << file.getFilename() << "'" << std::endl;

}

void Faces::load(std::string filename)
{
	BinaryFileReader file(filename);
	load(file);
}

void Faces::save(std::string filename) const
{
	BinaryFileWriter file(filename);
	save(file);
}

void Faces::save(BinaryFileWriter& file) const
{
	file.write(getSize());
	file.write(width);
	file.write(height);
	for (int i=0; i<getSize(); i++) {
		(*this)[i].save(file);
	}
	average_face.save(file);
	std::cout << "Saved faces to '" << file.getFilename() << "'" << std::endl;
}

void Faces::output(std::string filepattern) const
{
	for (int i=0; i<getSize(); i++) {
		// normalize for output
		Image out_image;
		(*this)[i].normalize(0.0, 255.0, out_image);
		std::string filename=Functions::filenameNumber(filepattern, i, getSize()-1);
		out_image.saveTarga(filename);
	}
}

void Faces::eigenFaces(EigFaces& results, int n) const
{
	// size the results vector
	results.resize(n);
	results.setHeight(height);
	results.setWidth(width);
	// --------- TODO #1: fill in your code to compute the first n eigenvaces and store them in results
	// also be sure you store the average face in results.average_face (A "set" method is provided for this).
	// You can use the sortEigenvalues function at the bottom of this file to help you find the
	// ordering of eigenvectors.
}



int Faces::getWidth() const
{
	return width;
}

int Faces::getHeight() const
{
	return height;
}

void Faces::setWidth(int width)
{
	width=width;
	vector_size=width*height;
}

void Faces::setHeight(int height)
{
	height=height;
	vector_size=width*height;
}

void Faces::sortEigenvalues(double *eigenvec, Array<int>& ordering) const
{
	// for now use simple bubble sort
	ordering.resize(vector_size);
	std::list<EigenVectorIndex> list;
	for (int i=0; i<vector_size; i++) {
		EigenVectorIndex e;
		e.eigenvalue=eigenvec[i+1];
		e.index=i;
		list.push_back(e);
	}
	bool change=true;
	list.sort();
	std::list<EigenVectorIndex>::iterator it=list.begin();
	int n=0;
	while (it!=list.end()) {
		ordering[n] = (*it).index;
		it++;
		n++;
	}
}

