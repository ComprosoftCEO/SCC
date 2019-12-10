#include "parser/c.tab.h"
#include "parser/c.yy.h"

#include <TranslationUnit.h>
#include <cstdio>

//
// Main entry point
//
int main(int argc, char** argv) {

  if (argc < 2) {
    fprintf(stderr, "scc: Error! No input file given!\n");
    fprintf(stderr, "Usage: %s <infile>\n", argv[0]);
    return 3;
  }

  // Open the file for reading
  FILE* file = fopen(argv[1], "r");
  if (file == NULL) {
    fprintf(stderr, "Error opening file '%s'!\n", argv[1]);
    return 1;
  }

  // Get everything ready to parse
  yyscan_t scanner;
  cclex_init(&scanner);
  ccset_in(file, scanner);

  TranslationUnit* unit;
  int result = ccparse(scanner, unit);

  cclex_destroy(scanner);
  fclose(file);

  if (unit != nullptr) { unit->print_code(); }
  delete (unit);

  return 0;
}
