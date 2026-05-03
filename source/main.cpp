
#include "Graph_DUMP.h"
#include "tree.h"
#include "akinator.h"
#include "TreeRead.h"

int main(){
    Tree_t tree = {};
    Node_Info progress = {}; 
    TreeFile text_tree = {};

    
    FILE* tree_text_file = fopen("tree.txt", "r");
    if (tree_text_file == nullptr) {
        perror("Error opening file");
        return 1;
    }

    ReadDataFromFile(&text_tree, tree_text_file, &tree);  
    fclose(tree_text_file);
    
    
    ProgressTreeInit(&progress, &tree);

    FILE* dot_file = fopen("tree.dot", "w");
    if (dot_file == nullptr) {
        perror("Error opening dot file");
    } else {
        DrawTree(&tree, tree.root, dot_file);  
        SetRankToNodes(&tree, &progress, dot_file); 
        FinishDotFile(dot_file);
        fclose(dot_file);
    }
    

    if (tree.root == nullptr) {
        printf("ERROR: Tree is empty! Cannot start game.\n");
        printf("Check your tree.txt file or create default tree.\n");
        return 1;
    }
    
    printf("Tree loaded successfully! Starting game...\n");
    printf("Root node: %s\n", tree.root->tree_data);
    
    GameMenuProcessing(&tree);
    
    return 0;
}