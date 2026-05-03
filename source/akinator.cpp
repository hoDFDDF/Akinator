#include "akinator.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <cassert>

UserAnswer GetUserAnswer() {
    char answer[MAX_OBJECT_NAME];
    
    while (1) {
        printf(" (y/n): ");
        GetLine(answer, sizeof(answer));
        
        if (strlen(answer) == 0) continue;
        
        char first_char = answer[0];
        if (first_char == 'y' || first_char == 'Y') {
            return YES;
        } else if (first_char == 'n' || first_char == 'N') {
            return NO;
        } else {
            printf("Please answer with 'y' or 'n'\n");
        }
    }
}

void GuessObject(Node_t* node) {
    assert(node != nullptr);

    while (node->left_child != nullptr && node->right_child != nullptr) {
        printf("%s", node->tree_data);
        
        UserAnswer answer = GetUserAnswer();
        
        if (answer == YES) {
            node = node->right_child;
        } else if (answer == NO) {
            node = node->left_child;
        }
    }
    
    printf("Is it %s?\n", node->tree_data);
    
    UserAnswer final_answer = GetUserAnswer();
    
    if (final_answer == YES) {
        printf("Hooray! I guessed it!\n");
    } else {
        printf("Oh, I was wrong...\n");
        AddNewObject(node);
    }
}

void AddNewObject(Node_t* current_node) {
    printf("What were you thinking of?\n");
    
    char new_object[MAX_OBJECT_NAME];
    GetLineWithPrompt("Enter object: ", new_object, sizeof(new_object));
    
    printf("How does %s differ from %s?\n", new_object, current_node->tree_data);
    
    char difference[MAX_OBJECT_NAME];
    GetLineWithPrompt("Enter difference: ", difference, sizeof(difference));
    
    char* old_object = strdup(current_node->tree_data);
    
    free((void*)current_node->tree_data);
    current_node->tree_data = strdup(difference);
    

    current_node->left_child = (Node_t*)calloc(1, sizeof(Node_t));
    if (current_node->left_child) {
        current_node->left_child->tree_data = strdup(old_object);
        current_node->left_child->left_child = nullptr;
        current_node->left_child->right_child = nullptr;
    }
    
    current_node->right_child = (Node_t*)calloc(1, sizeof(Node_t));
    if (current_node->right_child) {
        current_node->right_child->tree_data = strdup(new_object);
        current_node->right_child->left_child = nullptr;
        current_node->right_child->right_child = nullptr;
    }
    
    free(old_object);
    printf("Thanks! I've learned something new!\n");
}

void PrintObjectInfo(Tree_t* tree, const char* object_name) {
    PathResult path = FindPathToNode(tree->root, object_name);
    
    if (path.length == 0) {
        printf("Object '%s' not found\n", object_name);
        return;
    }
    
    printf("\n=== Information about '%s' ===\n", object_name);
    
    if (path.length == 1) {
        printf("This is a root object: %s\n", object_name);
    } else {
        printf("Path to object:\n");
        for (int i = 0; i < path.length; i++) {
            if (i == 0) {
                printf("Start: %s\n", path.path[i]->tree_data);
            } else if (i == path.length - 1) {
                printf("  -> Object: %s\n", path.path[i]->tree_data);
            } else {
                printf("  -> Has property: %s\n", path.path[i]->tree_data);
            }
        }
    }
    
    free(path.path);
}

void DescribeObject(Tree_t* tree, const char* object_name) {
    PathResult path = FindPathToNode(tree->root, object_name);
    
    if (path.length == 0) {
        printf("Object '%s' not found\n", object_name);
        return;
    }
    
    printf("\n=== Description of '%s' ===\n", object_name);
    
    if (path.length > 1) {
        printf("This is:\n");
        for (int i = 0; i < path.length - 1; i++) {
            printf("- %s\n", path.path[i]->tree_data);
        }
        printf("And specifically: %s\n", path.path[path.length - 1]->tree_data);
    } else {
        printf("Root object: %s\n", path.path[0]->tree_data);
    }
    
    free(path.path);
}


void CompareObjects(Tree_t* tree) {
    char obj1[MAX_OBJECT_NAME], obj2[MAX_OBJECT_NAME];
    
    printf("\n=== Compare two objects ===\n");
    GetLineWithPrompt("Enter first object: ", obj1, sizeof(obj1));
    GetLineWithPrompt("Enter second object: ", obj2, sizeof(obj2));
    
    PathResult path1 = FindPathToNode(tree->root, obj1);
    PathResult path2 = FindPathToNode(tree->root, obj2);
    
    if (path1.length == 0 || path2.length == 0) {
        printf("One or both objects not found\n");
        if (path1.path) free(path1.path);
        if (path2.path) free(path2.path);
        return;
    }
    
    printf("\n=== Comparison: %s vs %s ===\n", obj1, obj2);
    
    // Находим общие признаки
    int common = 0;
    while (common < path1.length && common < path2.length &&
           strcmp(path1.path[common]->tree_data, 
                  path2.path[common]->tree_data) == 0) {
        common++;
    }
    
    if (common > 0) {
        printf("\nCOMMON characteristics (%d):\n", common);
        for (int i = 0; i < common; i++) {
            printf("- %s\n", path1.path[i]->tree_data);
        }
    }
    
    printf("\nDIFFERENCES:\n");
    
    printf("\n%s:\n", obj1);
    if (common < path1.length) {
        for (int i = common; i < path1.length; i++) {
            if (i == common) {
                printf("- Specifically: %s", path1.path[i]->tree_data);
                if (i < path1.length - 1) printf(" (which has: ");
            } else if (i == path1.length - 1) {
                printf("%s)", path1.path[i]->tree_data);
            } else {
                printf("%s, ", path1.path[i]->tree_data);
            }
        }
        printf("\n");
    } else {
        printf("- No unique characteristics\n");
    }
    
    printf("\n%s:\n", obj2);
    if (common < path2.length) {
        for (int i = common; i < path2.length; i++) {
            if (i == common) {
                printf("- Specifically: %s", path2.path[i]->tree_data);
                if (i < path2.length - 1) printf(" (which has: ");
            } else if (i == path2.length - 1) {
                printf("%s)", path2.path[i]->tree_data);
            } else {
                printf("%s, ", path2.path[i]->tree_data);
            }
        }
        printf("\n");
    } else {
        printf("- No unique characteristics\n");
    }
    
    free(path1.path);
    free(path2.path);
}

// ========== ФУНКЦИИ МЕНЮ И ИНТЕРФЕЙСА ==========

// Функция вывода меню
void PrintGameMenu() {
    printf("\n+-----------------------------+\n");
    printf("|        AKINATOR MENU        |\n");
    printf("+-----------------------------+\n");
    printf("| [G]uess object             |\n");
    printf("| [D]escribe object          |\n");
    printf("| [C]ompare two objects      |\n");
    printf("| [I]nfo about object        |\n");
    printf("| [A]dd new object           |\n");
    printf("| [S]how knowledge tree      |\n");
    printf("| [E]xit and save            |\n");
    printf("+-----------------------------+\n");
    printf("Choose action: ");
}

void GameMenuProcessing(Tree_t* tree) {
    AkinatorMode mode = UNKNOWNMODE;
    bool exit_requested = false;
    
    printf("\n================================\n");
    printf("   WELCOME TO AKINATOR GAME!\n");
    printf("================================\n");
    printf("Think of an object, and I'll try to guess it!\n");
    
    do {
        PrintGameMenu();
        mode = GetAkinatorMode();
        
        switch (mode) {
            case GUESSOBJECT: {
                printf("\n=== GUESS MODE ===\n");
                printf("Think of an object. I'll try to guess it!\n");
                printf("Answer with 'y' for YES or 'n' for NO.\n\n");
                GuessObject(tree->root);
                break;
            }
            
            case DESCRIBEOBJECT: {
                printf("\n=== DESCRIBE MODE ===\n");
                char object[MAX_OBJECT_NAME];
                GetLineWithPrompt("Enter object name: ", object, sizeof(object));
                DescribeObject(tree, object);
                break;
            }
            
            case COMPAREOBJECT: {
                CompareObjects(tree);
                break;
            }
            
            case INFOMODE: {
                printf("\n=== INFO MODE ===\n");
                char object[MAX_OBJECT_NAME];
                GetLineWithPrompt("Enter object name: ", object, sizeof(object));
                PrintObjectInfo(tree, object);
                break;
            }
            
            case ADDINGMODE: {
                printf("\n=== ADD MODE ===\n");
                printf("I need to find where to add the new object...\n");
                
                Node_t* current = tree->root;
                char answer[MAX_OBJECT_NAME];
                
                while (current->left_child != nullptr && current->right_child != nullptr) {
                    printf("%s (y/n)? ", current->tree_data);
                    GetLine(answer, sizeof(answer));
                    
                    if (answer[0] == 'y' || answer[0] == 'Y') {
                        current = current->right_child;
                    } else if (answer[0] == 'n' || answer[0] == 'N') {
                        current = current->left_child;
                    } else {
                        printf("Please answer with 'y' or 'n'\n");
                    }
                }
                
                AddNewObject(current);
                break;
            }
            
            case SHOWTREE: {
                printf("\n=== KNOWLEDGE TREE ===\n");
                printf("Current tree structure:\n");
                PrintTree(tree->root, 0);
                break;
            }
            
            case EXIT: {
                printf("\n=== EXIT MODE ===\n");
                printf("Saving database to 'akinator_db.txt'...\n");
                SaveDataBase(tree, "akinator_db.txt");
                printf("Thank you for playing!\n");
                printf("Goodbye!\n");
                exit_requested = true;
                break;
            }
            
            case UNKNOWNMODE:
            default: {
                printf("Unknown command. Please try again.\n");
                break;
            }
        }
        
        if (!exit_requested) {
            printf("\nPress Enter to continue...");
            ClearInputBuffer();
        }
        
    } while (!exit_requested);
}

// Получение режима от пользователя
AkinatorMode GetAkinatorMode() {
    char input[MAX_OBJECT_NAME] = "";
    
    while (1) {
        GetLine(input, sizeof(input));
        
        if (strlen(input) == 0) {
            printf("Please enter a command: ");
            continue;
        }
        
        char choice = input[0];
        
        switch (choice) {
            case 'g':
            case 'G':
                printf("Starting Guess mode...\n");
                return GUESSOBJECT;
            case 'd':
            case 'D':
                printf("Starting Describe mode...\n");
                return DESCRIBEOBJECT;
            case 'c':
            case 'C':
                printf("Starting Compare mode...\n");
                return COMPAREOBJECT;
            case 'i':
            case 'I':
                printf("Starting Info mode...\n");
                return INFOMODE;
            case 'a':
            case 'A':
                printf("Starting Add mode...\n");
                return ADDINGMODE;
            case 's':
            case 'S':
                printf("Showing knowledge tree...\n");
                return SHOWTREE;
            case 'e':
            case 'E':
                printf("Exiting...\n");
                return EXIT;
            default:
                printf("Unknown command '%c'. Please try again.\n", choice);
                printf("Valid commands: G, D, C, I, A, S, E\n");
                printf("Choose action: ");
                break;
        }
    }
}

// ========== ФУНКЦИИ ВВОДА/ВЫВОДА ==========

// Чтение строки от пользователя
void GetLine(char* str, size_t max_size) {
    if (fgets(str, max_size, stdin) == NULL) {
        str[0] = '\0';
        return;
    }
    
    // Удаляем символ новой строки
    size_t len = strlen(str);
    if (len > 0 && str[len - 1] == '\n') {
        str[len - 1] = '\0';
    }
}

// Чтение строки с подсказкой
void GetLineWithPrompt(const char* prompt, char* buffer, size_t size) {
    printf("%s", prompt);
    GetLine(buffer, size);
}

// Очистка буфера ввода
void ClearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF) {}
}

// Поиск узла по имени объекта
Node_t* TreeSearch(Node_t* node, const char* object) {
    if (node == nullptr) return nullptr;
    
    if (strcmp(object, node->tree_data) == 0) return node;
    
    Node_t* node_left = TreeSearch(node->left_child, object);
    if (node_left) return node_left;

    Node_t* node_right = TreeSearch(node->right_child, object);
    return node_right;
}

// Рекурсивная функция поиска пути
static int FindPathRecursive(Node_t* current, Node_t* target, 
                             Node_t** path, int depth) {
    if (current == nullptr) return 0;
    
    path[depth] = current;
    
    if (current == target) {
        return depth + 1;
    }
    
    int left_len = FindPathRecursive(current->left_child, target, 
                                     path, depth + 1);
    if (left_len) return left_len;
    
    int right_len = FindPathRecursive(current->right_child, target, 
                                      path, depth + 1);
    return right_len;
}

// Поиск пути к узлу
PathResult FindPathToNode(Node_t* root, const char* object) {
    PathResult result = {nullptr, 0};
    
    Node_t* target_node = TreeSearch(root, object);
    if (target_node == nullptr) {
        return result;
    }
    
    size_t max_depth = MaxDepthOfBinaryTree(root);
    if (max_depth == 0) return result;
    
    Node_t** path = (Node_t**)calloc(max_depth, sizeof(Node_t*));
    if (path == nullptr) return result;
    
    int path_length = FindPathRecursive(root, target_node, path, 0);
    
    result.path = path;
    result.length = path_length;
    return result;
}

// Вычисление максимальной глубины дерева
size_t MaxDepthOfBinaryTree(Node_t* node) {
    if (node == nullptr) return 0;
    
    size_t left_depth = MaxDepthOfBinaryTree(node->left_child);
    size_t right_depth = MaxDepthOfBinaryTree(node->right_child);
    
    return (left_depth > right_depth ? left_depth : right_depth) + 1;
}

// Подсчет всех узлов в дереве
size_t CountNodes(Node_t* node) {
    if (node == nullptr) return 0;
    return 1 + CountNodes(node->left_child) + CountNodes(node->right_child);
}

// Подсчет листьев в дереве
size_t CountLeafNodes(Node_t* node) {
    if (node == nullptr) return 0;
    if (node->left_child == nullptr && node->right_child == nullptr) return 1;
    return CountLeafNodes(node->left_child) + CountLeafNodes(node->right_child);
}

// Вывод дерева в консоль
void PrintTree(Node_t* node, int depth) {
    if (node == nullptr) return;
    
    // Отступ в зависимости от глубины
    for (int i = 0; i < depth; i++) {
        printf("  ");
    }
    
    if (depth > 0) {
        printf("--:");
    }
    
    printf("%s\n", node->tree_data);
    
    // Рекурсивно печатаем детей
    PrintTree(node->left_child, depth + 1);
    PrintTree(node->right_child, depth + 1);
}

// ========== ФУНКЦИИ РАБОТЫ С БАЗОЙ ДАННЫХ ==========

// Сохранение базы данных в файл
void SaveDataBase(Tree_t* tree, const char* filename) {
    FILE* file = fopen(filename, "w");
    if (!file) {
        printf("Error opening file %s for writing\n", filename);
        return;
    }
    
    // Здесь должна быть логика сохранения дерева в файл
    // Пока просто заглушка
    fprintf(file, "# Akinator Database\n");
    fprintf(file, "# Total nodes: %zu\n", CountNodes(tree->root));
    
    fclose(file);
    printf("Database saved to %s\n", filename);
}

// Загрузка базы данных из файла (заглушка)
void LoadDatabase(Tree_t* tree, const char* filename) {
    printf("Loading database from %s...\n", filename);
    // Здесь должна быть логика загрузки дерева из файла
}

// ========== ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ ==========

// Показать статистику дерева
void ShowStatistics(Tree_t* tree) {
    printf("\n=== STATISTICS ===\n");
    printf("Total nodes in tree: %zu\n", CountNodes(tree->root));
    printf("Tree depth: %zu\n", MaxDepthOfBinaryTree(tree->root));
    printf("Number of leaf nodes: %zu\n", CountLeafNodes(tree->root));
}

// Поиск случайного объекта (заглушка)
void FindRandomObject(Tree_t* tree) {
    size_t total_nodes = CountNodes(tree->root);
    if (total_nodes == 0) {
        printf("Tree is empty!\n");
        return;
    }
    
    printf("I'm thinking of a random object...\n");
    printf("Random object from database: %s\n", tree->root->tree_data);
}

// Проверка существования объекта
bool ObjectExists(Tree_t* tree, const char* object_name) {
    return TreeSearch(tree->root, object_name) != nullptr;
}

// Получение списка всех объектов (заглушка)
char** GetAllObjects(Tree_t* tree, size_t* count) {
    *count = 0;
    return nullptr;
}