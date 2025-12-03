
#include "Graph_DUMP.h"
#include "tree.h"
#include "akinator.h"
#include "TreeRead.h"

int main(){
    Tree_t tree = {};
    Node_Info progress = {}; 
    TreeFile text_tree = {};

    // 1. Сначала парсим дерево из файла
    FILE* tree_text_file = fopen("tree.txt", "r");
    if (tree_text_file == nullptr) {
        perror("Error opening file");
        return 1;
    }

    // ПАРСИМ И ЗАПОЛНЯЕМ ДЕРЕВО
    ReadDataFromFile(&text_tree, tree_text_file, &tree);  // ← Нужно передать tree!
    fclose(tree_text_file);
    
    // 2. Инициализируем прогресс (если нужно для дампа)
    ProgressTreeInit(&progress, &tree);
    
    // 3. Создаем дамп (если нужно)
    FILE* dot_file = fopen("tree.dot", "w");
    if (dot_file == nullptr) {
        perror("Error opening dot file");
    } else {
        DrawTree(&tree, tree.root, dot_file);  // ← tree.root уже должен быть заполнен!
        SetRankToNodes(&tree, &progress, dot_file); 
        FinishDotFile(dot_file);
        fclose(dot_file);
    }
    
    // 4. Запускаем меню (ТОЛЬКО ЕСЛИ ДЕРЕВО НЕ ПУСТОЕ)
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