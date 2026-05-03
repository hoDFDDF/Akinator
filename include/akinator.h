#ifndef _AKINATOR_H_
#define _AKINATOR_H_

#include "tree.h"
#include "TreeRead.h"

// Константы
const size_t ANSWER_SIZE = 3;
const size_t MAX_OBJECT_NAME = 100;

// Режимы работы акинатора
typedef enum {
    GUESSOBJECT      = 0,  // Угадывание объекта
    DESCRIBEOBJECT   = 1,  // Описание объекта
    COMPAREOBJECT    = 2,  // Сравнение объектов
    INFOMODE         = 3,  // Информация об объекте
    ADDINGMODE       = 4,  // Добавление нового объекта
    SHOWTREE         = 5,  // Показать дерево знаний
    SAVEDATABASE     = 6,  // Сохранить базу данных
    EXIT             = 7,  // Выход
    UNKNOWNMODE      = 8   // Неизвестный режим
} AkinatorMode;

// Ответы пользователя
typedef enum {
    NO       = 0,
    YES      = 1,
    UNKNOWN  = 2
} UserAnswer;

// Структура для хранения пути к узлу
typedef struct {
    Node_t** path;   // Массив указателей на узлы
    int length;      // Длина пути (количество узлов)
} PathResult;


void GuessObject(Node_t* node);
void AddNewObject(Node_t* current_node);
void DescribeObject(Tree_t* tree, const char* object_name);
void CompareObjects(Tree_t* tree);
void PrintObjectInfo(Tree_t* tree, const char* object_name);а
void ShowStatistics(Tree_t* tree);

// ========== ФУНКЦИИ МЕНЮ И ИНТЕРФЕЙСА ==========

// Вывод главного меню
void PrintGameMenu();

// Обработка меню игры
void GameMenuProcessing(Tree_t* tree);

// Получение режима от пользователя
AkinatorMode GetAkinatorMode();

// Получение ответа от пользователя (да/нет)
UserAnswer GetUserAnswer();

// ========== ФУНКЦИИ ВВОДА/ВЫВОДА ==========

// Чтение строки от пользователя
void GetLine(char* str, size_t max_size);

// Чтение строки с подсказкой
void GetLineWithPrompt(const char* prompt, char* buffer, size_t size);

// Очистка буфера ввода
void ClearInputBuffer();

// ========== ФУНКЦИИ РАБОТЫ С ДЕРЕВОМ ==========

// Поиск узла по имени объекта
Node_t* TreeSearch(Node_t* node, const char* object);

// Поиск пути к узлу (от корня до целевого узла)
PathResult FindPathToNode(Node_t* root, const char* object);

// Вычисление максимальной глубины дерева
size_t MaxDepthOfBinaryTree(Node_t* node);

// Подсчет всех узлов в дереве
size_t CountNodes(Node_t* node);

// Подсчет листьев в дереве
size_t CountLeafNodes(Node_t* node);

// Вывод дерева в консоль
void PrintTree(Node_t* node, int depth);

// ========== ФУНКЦИИ РАБОТЫ С БАЗОЙ ДАННЫХ ==========

// Сохранение базы данных в файл
void SaveDataBase(Tree_t* tree, const char* filename);

// Загрузка базы данных из файла
void LoadDatabase(Tree_t* tree, const char* filename);

// ========== ДОПОЛНИТЕЛЬНЫЕ ФУНКЦИИ ==========

// Поиск случайного объекта
void FindRandomObject(Tree_t* tree);

// Проверка существования объекта
bool ObjectExists(Tree_t* tree, const char* object_name);

// Получение списка всех объектов
char** GetAllObjects(Tree_t* tree, size_t* count);

#endif // _AKINATOR_H_