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

#include "Page.h"

using namespace std;


void FIFO(vector<Page> pages, std::string outputFile, int frameSize) {
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

  for (std::vector<Page>::iterator it = pages.begin(); it != pages.end(); ++it, ++totalPageRequests) {
    found = false;
    for (int i = 0; i < pageListLength; ++i) {
      if (it->pageNumber() == pageList[i]) {
        found = true;
        break;
      }
    }
    if (found) {
      continue;
    }
    ++pageFaults;
    pageList[curr] = it->pageNumber();
    ++curr;
    ++pageListLength;
    if (pageListLength > frameSize) {
      pageListLength = frameSize;
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
  delete [] pageList;
}

void LRU(vector<Page> pages, std::string outputFile, int frameSize) {
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
  for (std::vector<Page>::iterator it = pages.begin(); it != pages.end(); ++it, ++totalPageRequests) {
    found = false;
    for (int i = 0; i < pageListLength; ++i) {
      if (it->pageNumber() == pageList[i]) {
        found = true;
        int temp = pageList[i];
        for (int j = i; j > 0; --j) {
          pageList[j] = pageList[j - 1];
        }
        pageList[0] = temp;
        break;
      }
    }
    if (found) {
      continue;
    }
    ++pageListLength;
    if (pageListLength > frameSize) {
      pageListLength = frameSize;
    }
    ++pageFaults;
    for (int i = pageListLength -1; i > 0; --i) {
      pageList[i] = pageList[i - 1];
    }
    pageList[0] = it->pageNumber();
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
  delete [] pageList;
}

void LFU(vector<Page> pages, std::string outputFile, int frameSize) {
  int pageListLength = 0;
  int totalPageRequests = 1;

  Page* pageList = new Page[frameSize];

  bool found = false;

  std::ofstream dataOut;

  float pageFaults = 0.0;
  float pageFaultRate2000 = 0.0;
  float pageFaultRate4000 = 0.0;
  float pageFaultRate6000 = 0.0;
  float pageFaultRate8000 = 0.0;
  float pageFaultRate10000 = 0.0;
  for (std::vector<Page>::iterator it = pages.begin(); it != pages.end(); ++it, ++totalPageRequests) {
    found = false;
    for (int i = 0; i < pageListLength; ++i) {
      if (it->pageNumber() == pageList[i].pageNumber()) {
        found = true;
        pageList[i].incTimesHit();
        break;
      }
    }

    bool sorted = false;
    int foo = 0;

    while(!sorted && pageListLength > 1) {  
      for (int i = 0; i < pageListLength; ++i) {
        if (((i + 1) < pageListLength) && pageList[i].timesHit() < pageList[i + 1].timesHit()) {
          Page temp = pageList[i + 1];
          pageList[i + 1] = pageList[i];
          pageList[i] = temp;
        } else if (i == pageListLength - 1 && pageList[i - 1].timesHit() >= pageList[i].timesHit()) {
          sorted = true;
        }
      }
    }

    if (found) {
      continue;
    }
    ++pageListLength;
    if (pageListLength > frameSize) {
      pageListLength = frameSize;
    }
    ++pageFaults;
    for (int i = pageListLength - 1; i > 0; --i) {
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
  dataOut << "LFU         " << pageFaults 
          << "                    " << pageFaultRate2000 
          << "  " << pageFaultRate4000
          << "  " << pageFaultRate6000
          << "  " << pageFaultRate8000
          << "  " << pageFaultRate10000 << endl;
  dataOut.close();
  delete [] pageList;
}


void Optimal(vector<Page> pages, std::string outputFile, int frameSize) {
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

  for (std::vector<Page>::iterator it = pages.begin(); it != pages.end(); ++it, ++totalPageRequests) {
    found = false;
    for (int i = 0; i < pageListLength; ++i) {
      if (it->pageNumber() == pageList[i]) {
        found = true;
        break;
      }
    }
    if (found) { 
      continue;
    }
    found = false;
    ++pageListLength;
    int longestDistIndex = 0;
    if (pageListLength > frameSize) {
      pageListLength = frameSize;
      int longestDist = 0;
      int currentDist = 0;
      for (int i = 0; i < pageListLength; ++i) {
        currentDist = 0;
        for (std::vector<Page>::iterator it2 = it; it2 != pages.end(); ++it2, ++currentDist) {
          if (pageList[i] == it2->pageNumber()) {
            found = true;
            break;
          }
        }
        if (currentDist > longestDist) {
          longestDist = currentDist;
          longestDistIndex = i;
        }
      }
      ++pageFaults;
      if (!found) {
        ++curr;
        curr %= frameSize; 
        pageList[curr] = it->pageNumber();
      } else {
        pageList[longestDistIndex] = it->pageNumber();
      }
    } else {
      ++pageFaults;
      pageList[curr] = it->pageNumber();
      ++curr;
      curr %= frameSize;
    }

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
  dataOut << "Optimal     " << pageFaults 
          << "                    " << pageFaultRate2000 
          << "  " << pageFaultRate4000
          << "  " << pageFaultRate6000
          << "  " << pageFaultRate8000
          << "  " << pageFaultRate10000 << endl;
  dataOut.close();
  delete [] pageList;
}

int main (int argc, char *argv[]) {
  if (argc > 4) {
    fprintf(stderr, "usage:  ucd-csci3453-Lab3 frameSize inputFile outputFile\n");
    exit(1);
  }

  int frameSize = atoi(argv[1]);
  std::string fileInName = argv[2];
  std::string fileOutName = argv[3];
  std::ifstream dataIn;
  std::ofstream dataOut;
  vector<Page> pageRequests;

  dataIn.open(fileInName);
  std::string s;

  while(true) {
    dataIn >> s;
    if (dataIn.eof()) {
      break;
    }
    Page temp = Page(stoi(s));
    pageRequests.push_back(temp);
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
