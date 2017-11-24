// Danny Cahoon
// Lab 3
// CSCI 3453


#include <fstream>
#include <iostream>
#include <string>
#include <unistd.h>
#include <vector>

#include <stdio.h>
#include <stdlib.h>

using namespace std;

void FIFO(vector<int> pages, std::string outputFile, int frameSize) {
  int curr = 0;
  int pageListLength = 0;
  int *pageList = new int[frameSize];
  int totalPageRequests = 1;

  bool found = false;
  
  std::ofstream dataOut;

  float pageFaults = 0.0;
  float pageFaultRate2000 = 0.0;
  float pageFaultRate4000 = 0.0;
  float pageFaultRate6000 = 0.0;
  float pageFaultRate8000 = 0.0;
  float pageFaultRate10000 = 0.0;

  for (std::vector<int>::iterator it = pages.begin(); it != pages.end(); ++it, ++totalPageRequests) {
    found = false;
    for (int i = 0; i < pageListLength; ++i) {
      if (*it == pageList[i]) {
        found = true;
        break;
      }
    }
    if (found) {
      continue;
    }
    ++pageFaults;
    pageList[curr] = *it;
    ++curr;
    ++pageListLength;
    if (pageListLength > 128) {
      pageListLength = 128;
    }
    curr %= frameSize;
    switch(totalPageRequests) {
    case 2000:
      pageFaultRate2000 = pageFaults / 2000.0;
      break;
    case 4000:
      pageFaultRate4000 = pageFaults / 4000.0;
      break;
    case 6000:
      pageFaultRate6000 = pageFaults / 6000.0;
      break;
    case 8000:
      pageFaultRate8000 = pageFaults / 8000.0;
      break;
    case 10000:
      pageFaultRate10000 = pageFaults / 10000.0;
      break;
    }
  }
  dataOut.open(outputFile, std::ios::app);
  dataOut << "FIFO        " << pageFaults 
          << "                    " << pageFaultRate2000 
          << "  " << pageFaultRate4000
          << "  " << pageFaultRate6000
          << "  " << pageFaultRate8000
          << "  " << pageFaultRate10000 << endl;
  dataOut.close();
}

void LRU(vector<int> pages, std::string outputFile, int frameSize) {
  int pageListLength = 0;
  int *pageList = new int[frameSize];
  int totalPageRequests = 1;

  bool found = false;
  std::ofstream dataOut;

  float pageFaults = 0.0;
  float pageFaultRate2000 = 0.0;
  float pageFaultRate4000 = 0.0;
  float pageFaultRate6000 = 0.0;
  float pageFaultRate8000 = 0.0;
  float pageFaultRate10000 = 0.0;
  for (std::vector<int>::iterator it = pages.begin(); it != pages.end(); ++it, ++totalPageRequests) {
    found = false;
    for (int i = 0; i < pageListLength; ++i) {
      if (*it == pageList[i]) {
        found = true;
        ++pageListLength;
        if (pageListLength > 128) {
          pageListLength = 128;
        }
        int temp = pageList[i];
        for (int j = i; i > 0; --i) {
          if (j == 0) {
            pageList[0] = temp;
            break;
          }
          pageList[j] = pageList[j - 1];
        }
        break;
      }
    }
    if (found) {
      continue;
    }
    ++pageListLength;
    if (pageListLength > 128) {
      pageListLength = 128;
    }
    ++pageFaults;
    for (int i = pageListLength; i > 0; --i) {
      pageList[i] = pageList[i - 1];
    }
    pageList[0] = *it;
    switch(totalPageRequests) {
    case 2000:
      pageFaultRate2000 = pageFaults / 2000.0;
      break;
    case 4000:
      pageFaultRate4000 = pageFaults / 4000.0;
      break;
    case 6000:
      pageFaultRate6000 = pageFaults / 6000.0;
      break;
    case 8000:
      pageFaultRate8000 = pageFaults / 8000.0;
      break;
    case 10000:
      pageFaultRate10000 = pageFaults / 10000.0;
      break;
    }
  }
  dataOut.open(outputFile, std::ios::app);
  dataOut << "LRU         " << pageFaults 
          << "                    " << pageFaultRate2000 
          << "  " << pageFaultRate4000
          << "  " << pageFaultRate6000
          << "  " << pageFaultRate8000
          << "  " << pageFaultRate10000 << endl;
  dataOut.close();
}

void LFU(vector<int> pages, std::string outputFile, int frameSize) {
  int curr = 0;
  int pageListLength = 0;
  int *pageList = new int[frameSize];
  int totalPageRequests = 1;

  bool found = false;
  std::ofstream dataOut;

  float pageFaults = 0.0;
  float pageFaultRate2000 = 0.0;
  float pageFaultRate4000 = 0.0;
  float pageFaultRate6000 = 0.0;
  float pageFaultRate8000 = 0.0;
  float pageFaultRate10000 = 0.0;
  for (std::vector<int>::iterator it = pages.begin(); it != pages.end(); ++it, ++totalPageRequests) {
    found = false;
  }
  dataOut.open(outputFile, std::ios::app);
  dataOut << "LFU         " << pageFaults 
          << "                    " << pageFaultRate2000 
          << "  " << pageFaultRate4000
          << "  " << pageFaultRate6000
          << "  " << pageFaultRate8000
          << "  " << pageFaultRate10000 << endl;
  dataOut.close();
}

void Optimal(vector<int> pages, std::string outputFile, int frameSize) {
  int curr = 0;
  int pageListLength = 0;
  int *pageList = new int[frameSize];
  int totalPageRequests = 1;

  bool found = false;
  std::ofstream dataOut;

  float pageFaults = 0.0;
  float pageFaultRate2000 = 0.0;
  float pageFaultRate4000 = 0.0;
  float pageFaultRate6000 = 0.0;
  float pageFaultRate8000 = 0.0;
  float pageFaultRate10000 = 0.0;
  for (std::vector<int>::iterator it = pages.begin(); it != pages.end(); ++it, ++totalPageRequests) {
    found = false;
  }
  dataOut.open(outputFile, std::ios::app);
  dataOut << "Optimal     " << pageFaults 
          << "                    " << pageFaultRate2000 
          << "  " << pageFaultRate4000
          << "  " << pageFaultRate6000
          << "  " << pageFaultRate8000
          << "  " << pageFaultRate10000 << endl;
  dataOut.close();
}

int main (int argc, char *argv[]) {
  if (argc > 4) {
    fprintf(stderr, "usage:  ucd-csci3453-Lab3 frame_size inputFile outputFile\n");
    exit(1);
  }

  int frameSize = atoi(argv[1]);
  std::string fileInName = argv[2];
  std::string fileOutName = argv[3];
  std::ifstream dataIn;
  std::ofstream dataOut;
  vector<int> pageRequests;

  dataIn.open(fileInName);
  std::string s;

  while(true) {
    dataIn >> s;
    if (dataIn.eof()) {
      break;
    }
    pageRequests.push_back(stoi(s));
  }
  dataIn.close();

  dataOut.open(fileOutName, std::ios::app);
  dataOut << "==============================================================" << endl;
  dataOut << "    Page Replacement Algorithm Simulation (frame size = " << frameSize << ")" << endl;
  dataOut << "==============================================================" << endl;
  dataOut << "                                       Page Fault Rates" << endl;
  dataOut << "Algorithm  Total page faults     2000  4000  6000  8000  10000" << endl;
  dataOut << "--------------------------------------------------------------" << endl;
  dataOut.close();
  FIFO(pageRequests, fileOutName, frameSize);
  LRU(pageRequests, fileOutName, frameSize);
  LFU(pageRequests, fileOutName, frameSize);
  Optimal(pageRequests, fileOutName, frameSize);
  return 0;
}
