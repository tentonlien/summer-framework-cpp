/* Created by Tenton Lien on 1/13/2020 */

#ifndef FILE_SCANNER_H
#define FILE_SCANNER_H

#include <string>

class FileScanner {
  public:
    FileScanner();

  private:
    void scan();
    void scan(std::string);
};


#endif