// Page.cpp
#include "Page.h"

Page::Page() : pageNumber_(0), timesHit_(0) {
}

Page::Page(int pageNumber) : pageNumber_(pageNumber), timesHit_(0) {
}

Page::~Page() {
}

int Page::pageNumber() {
	return this->pageNumber_;
}

int Page::timesHit() {
	return	this->timesHit_;
}

void Page::setPageNumber(int pageNumber) {
	this->pageNumber_ = pageNumber;
}

void Page::setTimesHit(int timesHit) {
	this->timesHit_ = timesHit;
}

void Page::incTimesHit() {
	this->timesHit_ += 1;
}