#include <iostream>
#include<stdio.h>
#include<fstream>
#include<string>
#include<vector>
#include <bits/stdc++.h>
#include <ctime>

using namespace std;

struct node
{
    bool color;       //0 stands for red 1 stands for black
    char key[30];
    node *left;
    node *right;
    node *parent;
};


node *root;


node* createNode(char data[], node* ilBaba)
{
    node * newNode = new node;
    strcpy(newNode->key,data);
    newNode->color = 0;
    newNode->left  = NULL;
    newNode->right = NULL;
    newNode->parent = ilBaba ;
    return newNode;

}


void inorder(struct node *root)
{
    if (root != NULL)
    {
        inorder(root->left);
        cout<<" "<<root->key<<endl<<" color: "<<root->color<<endl;

        inorder(root->right);
    }
}


void rotateRight(node *&root, node *&ptr) 
{ 
    node *ptr_left = ptr->left; 
  
    ptr->left = ptr_left->right; 
  
    if (ptr->left != NULL) 
        ptr->left->parent = ptr; 
  
    ptr_left->parent = ptr->parent; 
  
    if (ptr->parent == NULL) 
        root = ptr_left; 
  
    else if (ptr == ptr->parent->left) 
        ptr->parent->left = ptr_left; 
  
    else
        ptr->parent->right = ptr_left; 
  
    ptr_left->right = ptr; 
    ptr->parent = ptr_left; 
} 


void rotateLeft(node *&root, node *&parent) 
{ 
    node *parentRight = parent->right; 
  
    parent->right = parentRight->left; 
  
    if (parent->right != NULL) 
        parent->right->parent = parent; 
  
    parentRight->parent = parent->parent; 
  
    if (parent->parent == NULL) 
        root = parentRight; 
  
    else if (parent == parent->parent->left) 
        parent->parent->left = parentRight; 
  
    else
        parent->parent->right = parentRight; 
  
    parentRight->left = parent; 
    parent->parent = parentRight; 
} 



void profix(node *&root , node *&newNode)
{
	/*printf("da5al el profix\n");
	printf("%s\n",root->key);
	printf("%s\n",newNode->key);*/
	node *parent = NULL;
	node*grandParent = NULL;
	
	while ((newNode != root) && (newNode->color != 1) && (newNode->parent->color == 0))
	{
		
		parent = newNode->parent; 
        grandParent = newNode->parent->parent;
        /*printf("parent of newnode %s\n",parent->key);
        printf("grandparent of newnode %s\n",grandParent->key);*/
		
		if(parent == grandParent->left) //uncle right parent left
		{	
			//printf("da5al uncle right\n");
			node *uncle = grandParent->right;
			
			if((uncle != NULL) && (uncle->color == 0)) //uncle red (case 1)  
			{							
				//printf("da5al case 1\n");
				grandParent->color = 0; 
                parent->color = 1; 
                uncle->color = 1; 
                newNode = grandParent;
				//printf("color el grandpa %d\n",newNode->color); 
			}
			else // uncle black or NILL (case 2) 
			{
				//printf("da5al case 2");
				if(newNode == parent->right) //left right // child right of parent
				{
					//printf("da5al left right\n");
					//printf("old parent %s\n",parent->key);
					rotateLeft(root, parent); 
                    newNode = parent; 
                    parent = newNode->parent;
					//printf("new parent %s\n",parent->key); 
				}
				else // left left
				{
					//printf("da5al left left\n");
					rotateRight(root, grandParent); 
               		swap(parent->color, grandParent->color); 
              		newNode = parent; 
				}
				
			}
		}  
		else //uncle left
		{
			//printf("da5al uncle left\n");
			node *uncle = grandParent->left;
			
			if((uncle != NULL) && (uncle->color == 0)) //uncle red (case 1)
			{
				//printf("da5al case 1\n");
				grandParent->color = 0; 
                parent->color = 1; 
                uncle->color = 1; 
                newNode = grandParent; 	
			}
			else // uncle black or NILL
			{
				//printf("da5al case 2\n");
				if(newNode == parent->left) //right left
				{
					//printf("da5al right left\n");
					rotateRight(root, parent); 
                    newNode = parent; 
                    parent = newNode->parent; 
				}
				else //right right
				{
					//printf("da5al right right\n");
					rotateLeft(root, grandParent); 
                	swap(parent->color, grandParent->color); 
              		newNode = parent; 
				}
			}
			
		} 
	}
	root->color = 1;
	 
}


node * insertion(node *root,char data[])
{
    node  *temp = root;
    node *newNode;
    if(root==NULL)
    {
    	//printf("da5al root insertion\n");
        root = createNode(data, NULL);
        root->color = 1;

        return root;

    }
    else
    {
		//printf("da5al f else el insertion\n");
        while(temp!=NULL)
        {
            if(strcasecmp(temp->key,data)>0 || strcasecmp(temp->key,data) == 0)
            {
                if(temp->left==NULL)
                {
                    newNode = createNode(data,temp);
                    temp->left=newNode;

                    break;
                }

                else
                    temp = temp->left;

            }

            else if(strcasecmp(temp->key,data)<0)
            {

                if(temp->right==NULL)
                {
                    newNode = createNode(data,temp);
                    temp->right=newNode;
                    break;
                }
                else
                    temp = temp->right;

            }
        }
        
    }
    profix(root,newNode);
    return root;
}



int sizeOfTree( node *root)
{

    return (root == NULL) ? 0 :
           1 + sizeOfTree(root->left) + sizeOfTree(root->right);

}


int  MAX(int h1, int h2)
{
    if(h1>h2)
        return h1;

    else if(h1<h2)
        return h2;
    else
        return h1;

}

int height( node *root)
{

    return (root == NULL) ? -1 : 1+ MAX(height(root->left), height(root->right));
}

void search(node *root, char data[])
{

    if (root == NULL)
    {
        cout<<"Not found"<<endl;
	}
    else if (strcmp(data,root->key) == 0)
    {
    	cout<<data<<"---Found"<<endl;
	}         
    else if (strcmp(data,root->key) < 0)
    {
    	root = root->left;
    	return search(root, data);
	} 
    else
    {
    	root = root->right;
    	return search(root, data);
	}
}



int main()
{
    FILE * fp = fopen("dic.txt","r");
    if (fp == NULL)
    {
        printf("File not found!");
        exit(0);
    }
    char  Word[50];
    char str[50];
    char *token;

	node *root = NULL;




    while(!feof(fp))
    {

        //fgets (Word, 50, fp);
        fscanf(fp, "%s", Word);
        root = insertion(root,Word);
    
    }
    
    fclose(fp);

	inorder(root);	
	cout<<"The root is "<<root->key;

    printf("The size of the tree: %d\n",sizeOfTree(root));
    printf("The height of the tree:%d\n",height(root));
    printf("Enter a word:\n");

	int x = 5;
    while(x != 0)
    {
        gets(str);
        search(root,str);
    	x--;
    }

    return 0;
}
