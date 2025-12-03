#include "akinator.h"

void GuessObject(Node_t* node){
    assert(node != nullptr);

    char answer[ANSWER_SIZE];

    while (node->left_child != nullptr && node->right_child != nullptr) {
        printf("You guess %s (y/n)?", node->tree_data);

        GetLine(answer);

        fscanf(stdin, "%s", answer);
    
        if (strcmp(answer, "y") == 0) {

            node = node->right_child;

        } else if (strcmp(answer, "n")) {
            node = node->left_child;
        }
        else{
            printf("I didn't understand you, try again");
        }
    }
    
}

void PrintGameMenu(){
    printf(" ====MENU====\n");
    printf("[C]ompare objects\n");
    printf("[G]uess objects\n");
    printf("[A]dd new object\n");
    printf("[E]xit\n");
    
}

void GetLine(char* str){
    char ch = 0;
    size_t str_len = 0;

    while ((ch = getchar()) != EOF) {
        
        if (ch == '\n') {
            str[str_len] = '\0';
        }

        str[str_len] = ch;
        str_len++;
    } 
}

void GameMenuProcessing(Tree_t* tree, Node_t* node){
    do {
        PrintGameMenu();
        
        char mode = GetAkinatorMode();

        switch (mode)
        {
            case GUESSOBJECT:
                GuessObject(tree->root);
                return;
            case SAVEDATABASE:
                SaveDataBase();
            case ADDINGMODE:
                AddNewObject();
                break;
            
            default:
                break;
        }
    }

    while();
    
}

AkinatorMode GetAkinatorMode(){

    char mode[MAX_LENGHT_OF_TEMP_BUFFER] = "";

    GetLine(mode);
    
    switch (*mode) {
        case 'C':
        case 'c':
            printf("Starting Comparing Mode....\n");
            return COMPAREOBJECT;
        case 'A' :
        case 'a' :
            printf("Starting Adding Mode....\n");
            return ADDINGMODE;
        case 'G':
        case 'g':
            return GUESSOBJECT;
        case 'E':
        case 'e':
            return EXIT;
        default:
            return UNNOWNMODE;
    }

}

void GetUserAnwer(){
    
}

void AddNewObject(){

}

void PrintObjectInfo(){
    
}

void DescribeObject(){

}




Node_t* TreeSearch(Tree_t* tree, Node_t* node, char* object){
    if (node == nullptr) return nullptr;
   
    if (strcmp(object, node->tree_data) == 0) return node;
    
    Node_t* node_left = TreeSearch(tree, node->left_child, object);
    if (node_left) return node_left;

    Node_t* node_right = TreeSearch(tree, node->right_child, object);
    if (node_right) return node_right;
    
}

Node_t** FindPathToNode(Node_t* node){

    const size_t MAX_DEPTH = MaxDepthOfBInaryTree(node);

    Node_t* path[MAX_DEPTH];
    
    if (n)

}