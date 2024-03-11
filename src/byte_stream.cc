#include "byte_stream.hh"
#include <string>

using namespace std;

// uint64_t capacity_;
// std::string buf_;
// uint64_t npush_, npop_;
// bool is_close_;
// bool error_ {};
ByteStream::ByteStream( uint64_t capacity )
  : capacity_( capacity ), buf_(), view_( "" ), npush_( 0 ), npop_( 0 ), is_close_( false ), error_( false )
{}

bool Writer::is_closed() const
{
  return this->is_close_;
}

void Writer::push( string data )
{
  // TODO: Your code here.
  (void)data;
  uint64_t len = min( available_capacity(), data.size() );
  npush_ += len;
  buf_.insert( buf_.end(), data.begin(), data.begin() + len );
  return;
}

void Writer::close()
{
  is_close_ = true;
}

uint64_t Writer::available_capacity() const
{
  return capacity_ - buf_.size();
}

uint64_t Writer::bytes_pushed() const
{
  return npush_;
}

bool Reader::is_finished() const
{
  return is_close_ && buf_.size() == 0;
}

uint64_t Reader::bytes_popped() const
{
  return npop_;
}

string_view Reader::peek() const
{
  this->view_ = std::string( buf_.begin(), buf_.end() );
  return string_view( view_ );
}

void Reader::pop( uint64_t len )
{
  // TODO: Your code here.
  len = min( len, bytes_buffered() );
  npop_ += len;
  while ( len-- )
    buf_.pop_front();
}

uint64_t Reader::bytes_buffered() const
{
  return buf_.size();
}
