#include "TreeRead.h"
#include "tree.h"

void ReadDataFromFile(TreeFile* text_tree, FILE* tree_file_ptr, Tree_t* tree){
    assert(text_tree != nullptr);
    assert(tree != nullptr);

    char temp_buffer_data[MAX_LENGHT_OF_TEMP_BUFFER];
    char* tree_file_string = fgets(temp_buffer_data, MAX_LEGHT_OF_DATA, tree_file_ptr);    
    
    if (tree_file_string == nullptr) {
        printf("ERROR: Failed to read from file\n");
        return;
    }
    
    printf("Read string: %s\n", tree_file_string);  // ДЕБАГ
    
    // Парсим дерево
    char* str_ptr = tree_file_string;
    tree->root = NodeParse(&str_ptr);  
    
    if (tree->root == nullptr) {
        printf("ERROR: Failed to parse tree from file\n");
    } else {
        printf("Tree parsed successfully. Root: %s\n", tree->root->tree_data);
    }
}

Node_t* NodeParse(char** tree_str){

    while (**tree_str == ' ') (*tree_str)++;
    
    if (**tree_str == ')') {
        (*tree_str)++;   
        return nullptr;
    }
    
    if (**tree_str != '(') {
        return nullptr;
    }
    
    (*tree_str)++;
    
    char node_name[MAX_LEGHT_OF_DATA];
    size_t name_len = 0;
    
    while (**tree_str && **tree_str != ' ' && **tree_str != ')') {
        if (name_len < MAX_LEGHT_OF_DATA - 1) {
            node_name[name_len] = **tree_str;
            name_len++;
        } else {
            return nullptr;
        }
        (*tree_str)++;
    }
    
    node_name[name_len] = '\0';
    
    while (**tree_str == ' ') (*tree_str)++;
    
    Node_t* node = (Node_t*)calloc(1, sizeof(Node_t));
    if (!node) return nullptr;
    
    node->tree_data = strdup(node_name);
    
    if (!node->tree_data) {
        free(node);
        return nullptr;
    }
    
    if (**tree_str != ')') {
        node->left_child = NodeParse(tree_str);
        
        while (**tree_str == ' ') (*tree_str)++;
        
        //if (**tree_str != ')') {
            node->right_child = NodeParse(tree_str);
        //}
    }
    
    if (**tree_str == ')') {
        (*tree_str)++;
    }
    
    return node;
}

