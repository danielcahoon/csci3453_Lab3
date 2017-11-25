#ifndef PAGE_H
#define PAGE_H
class Page {
  private:
    int pageNumber_;
    int timesHit_;
  public:
    // constructors
    Page();
    Page(int pageNumber);
    
    // destructor
    ~Page();

    // getters
    int pageNumber();
    int timesHit();
    
    // setters
    void setPageNumber(int pageNumber);
    void setTimesHit(int timesHit);

    // member functions
    void incTimesHit();
};
#endif