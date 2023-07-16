#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE_CHAR 26

typedef struct Node
{
    struct Node *children[SIZE_CHAR];
    bool endword;
} Node;

Node *CreateNode()
{
    Node *newnode = (Node *)malloc(sizeof(Node));

    for (int i = 0; i < SIZE_CHAR; i++)
    {
        newnode->children[i] = NULL;
    }

    newnode->endword = false;

    return newnode;
}

int EmptyTrie(Node *root)
{
    for (int i = 0; i < SIZE_CHAR; i++)
    {
        if (root->children[i] != NULL)
        {
            return false;
        }
    }
    printf("\n\nEMPTY TREE !\n\n");
    exit(0);
    return true;
}

int InsertTrie(Node *root, char *word)
{
    Node *current = root;
    int index;
    int len = strlen(word);

    for (int i = 0; i < len; i++)
    {
        index = word[i] - 'a';

        if (current->children[index] == NULL)
        {
            current->children[index] = CreateNode();
        }

        current = current->children[index];
    }

    current->endword = true;

    return 1;
}

bool search(Node *root, char *word)
{
    Node *current = root;
    int index;
    int len = strlen(word);

    EmptyTrie(root);

    for (int i = 0; i < len; i++)
    {
        index = word[i] - 'a';

        if (current->children[index] == NULL)
        {
            return false;
        }

        current = current->children[index];
    }

    if (current->endword)
    {
        return true;
    }
    else
    {
        return false;
    }
}

int SearchTrie(Node *root, char *word)
{
    if(search(root,word))
    {
        printf("\n\nWord was found: %s\n\n",word);
    }
    else
    {
        printf("\n\nWord NOT found: %s\n\n",word);
    }
}

int PrintTrie(Node *root, char *str, int index)
{
    Node *aux = root;

    if (aux->endword)
    {
        str[index] = '\0';
        printf("%s\n", str);
    }

    for (int i = 0; i < SIZE_CHAR; i++)
    {
        if (aux->children[i] != NULL)
        {
            str[index] = i + 'a';
            PrintTrie(aux->children[i], str, index + 1);
        }
    }

    return 1;
}

bool EmptyNode(Node *root)
{
    for (int i = 0; i < SIZE_CHAR; i++)
    {
        if (root->children[i] != NULL)
        {
            return false;
        }
    }

    return true;
}

Node *removed(Node *root, char *word, int init)
{
    if (root == NULL)
    {
        return NULL;
    }

    if (init == strlen(word))
    {
        root->endword = false;

        if (EmptyNode(root))
        {
            free(root);
            root = NULL;
        }
        return root;
    }

    int index = word[init] - 'a';

    root->children[index] = removed(root->children[index], word, init + 1);

    if (EmptyNode(root) && !root->endword)
    {
        free(root);
        root = NULL;
    }

    return root;
}

int RemovedTrie(Node *root, char *word,int init)
{
    if(search(root,word))
    {
        removed(root,word,0);
        printf("\n\nWord remove: %s\n\n",word);
    }
    else
    {
        printf("\n\nWord NOT found to remove: %s\n\n",word);
    }
}

int main()
{
    Node *root = CreateNode();
    char str[50];

    InsertTrie(root,"horse");
    InsertTrie(root,"bat");
    InsertTrie(root,"bullet");
    InsertTrie(root,"house");

    PrintTrie(root,str,0);

    SearchTrie(root,"horse");
    SearchTrie(root,"dog");

    RemovedTrie(root,"bullet",0);
    RemovedTrie(root,"genshin",0);
    printf("\n\n");
    PrintTrie(root,str,0);
}