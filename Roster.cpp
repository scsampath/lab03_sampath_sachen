//Edited by Sachen Sampath, CS32, 4/24/2020
#include "Roster.h"

#include <cstdlib>
#include <fstream>
#include <cassert>
#include <sstream>

Roster::Roster() {
  // initialize to empty array

  this->numStudents = 0;
  for (int i=0; i<ROSTER_MAX; i++) {
    this->students[i] = NULL;
  }

}

void Roster::resetRoster() {
 // To avoid memory leaks:
  //  Recycle memory for all allocated students on roster
  
  while (this->numStudents > 0) {
    delete this->students[this->numStudents - 1];
    this->numStudents --;
  }

}

void Roster::addStudentsFromFile(std::string filename) {
  std::ifstream ifs; // the stream we will use for the input file
  ifs.open(filename);
  
  if (ifs.fail()) {
    std::cerr << "Could not open input file: "
	      << filename << std::endl;
    exit(2); 
  }

  // ifs is an instance of ifstream
  // ifstream inherits from istream, 
  //   i.e. ifs is-a istream

  this->addStudentsFromStream(ifs);

}

void Roster::addStudentsFromStream(std::istream &is) {

  this->resetRoster();

  std::string thisLine;
  // Try to read past the header line.
  getline(is,thisLine);
  if ( is.eof() || is.fail() ) {
    std::cerr << "Unable to read first line of input stream" << std::endl;
    exit(3);
  }

  getline(is,thisLine);
  while (  !is.eof() && !is.fail() ) {
    // If we get here, it means the most recent attempt to read succeeded!
    // So do something with thisLine
    
    Student *sPtr = new Student(thisLine);
    this->students[this->numStudents] = sPtr;
    this->numStudents++;
    
    // try to read another line
    getline(is,thisLine);
  } // end while

}

int Roster::getNumStudents() const { 
  return this->numStudents; 
}

Student Roster::getStudentAt(int index) const { 
  return *students[index];
}

std::string Roster::toString() const {
  std::ostringstream oss;
  
  oss << "{" << "\n";
  for(int i = 0; i < numStudents; i++){
    oss << "[" 
      << this->students[i]->getPerm() << ","
      << this->students[i]->getLastName() << ","
      << this->students[i]->getFirstAndMiddleNames() << "]";
      if(i != numStudents - 1){
        oss << ",";
      }
      oss << "\n";
  }
  oss << "}" << "\n";
  return oss.str();

}

void Roster::sortByPerm() {
  // SELECTION SORT
  for(int i = 0; i < numStudents; i++){
    sortByPermHelper(numStudents - i);
  }
}

int Roster::indexOfMaxPermAmongFirstKStudents(int k) const {
  int max = students[0]->getPerm();
  int index = 0;
  for(int i = 1; i < k; i++){
    if(students[i]->getPerm() > max){
      max = students[i]->getPerm();
      index = i;
    }
  }
  return index;
}

void Roster::sortByPermHelper(int k) {
  // swaps max perm from [0..k-1] with elem [k-1]


  int im = indexOfMaxPermAmongFirstKStudents(k);

  // now swap the pointers between index im and index k-1
  Student *temp = students[k-1];
  students[k-1] = students[im];
  students[im] = temp;
}
