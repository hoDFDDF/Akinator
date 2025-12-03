
#include "Graph_DUMP.h"
#include "tree.h"
#include "akinator.h"
#include "TreeRead.h"

int main(){
    Tree_t tree = {};
    Node_t node = {};
    Node_Info progress = {}; 
    TreeFile text_tree = {};

    ProgressTreeInit(&progress, &tree);
    FILE* dot_file = fopen("tree.dot", "w");
    if (dot_file == nullptr) perror("Error opening file");

    FILE* tree_text_file = fopen("tree.txt", "r");
    if (tree_text_file == nullptr) perror("Error opening file");


    ReadDataFromFile(&text_tree, tree_text_file);
    DrawTree(&tree, &node, dot_file); 

    SetRankToNodes(&tree, &progress, dot_file); 
    FinishDotFile(dot_file);
    
    fclose(dot_file);

    return 0;
}