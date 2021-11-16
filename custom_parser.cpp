#include "config.h"
#include "custom_parser.h"
#include "JsonListener.h"

enum STATE {NOT_FOUND, FOUND_CONTENT, FOUND_AUTHOR};
static STATE key_found; 

extern char quote_string[MAX_QUOTE_LENGTH];
extern char author_string[MAX_AUTHOR_LENGTH];

void quoteListener::whitespace(char c) {
}

void quoteListener::startDocument() {
  key_found = NOT_FOUND;
}

void quoteListener::key(String key) {
  if(key.equals("content")){
    key_found = FOUND_CONTENT;
  } else if (key.equals("author")){
    key_found = FOUND_AUTHOR;
  }
}

void quoteListener::value(String value) {
  if(key_found == FOUND_CONTENT){
    strncpy(quote_string, (char*)value.c_str(), MAX_QUOTE_LENGTH);
    DEBUG.printf("Quote: %s\n", quote_string);
    key_found = NOT_FOUND;
  } else if(key_found == FOUND_AUTHOR){
    strncpy(author_string, (char*)value.c_str(), MAX_AUTHOR_LENGTH);
    DEBUG.printf("Author: %s\n", author_string);
    key_found = NOT_FOUND;
  }
}

void quoteListener::endArray() {
}

void quoteListener::endObject() {
}

void quoteListener::endDocument() {
}

void quoteListener::startArray() {
}

void quoteListener::startObject() {
}

size_t ArudinoStreamParser::write(const uint8_t *data, size_t size) {
    
  uint8_t char_val = 0x00;
  
  if(size && data) {
    for (size_t idx=0; idx<size; idx++)
    {
      char_val = *(data + idx);
      parse(char_val);
    }
    return size;    
  }
  
    return 0;
}

size_t ArudinoStreamParser::write(uint8_t data) {
  
  parse(data);
  
  return 1;
}

int ArudinoStreamParser::available() {
    return 1;
}

int ArudinoStreamParser::read() {
    return -1;
}

int ArudinoStreamParser::peek() {
    return -1;
}

void ArudinoStreamParser::flush() {
}
