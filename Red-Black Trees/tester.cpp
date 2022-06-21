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

void rotateLeft(node *newNode)
{
	node *temp;
	node *grandParent = newNode;   //grandparent hyb2a esmo parent
	node *parent = grandParent->right; //parent hyb2a esmo child
	if(parent->left != NULL)
	{
		temp = parent->left;
		grandParent->right = temp;
		parent->left = grandParent;	
	}
	else
	{
		parent->left = grandParent;
		grandParent->right = NULL;
	}
	
}

void rotateRight(node *newNode) //case if I send the parent 
{
	node *temp;
	node *grandParent = newNode;   //grandparent hyb2a esmo parent
	node *parent = grandParent->left; //parent hyb2a esmo child
	if(parent->right != NULL)
	{
		temp = parent->right;
		grandParent->left = temp;
		parent->right = grandParent;	
	}
	else
	{
		parent->right = grandParent;
		grandParent->left = NULL;
	}
		
}

void proFix(node * newNode)
{
	
	if(newNode->parent != NULL)
	{
		
		if(newNode->parent->parent != NULL)
		{
		
			node *grandParent = newNode->parent->parent;
        	node *parent = newNode->parent;

    		if(parent->color==0)
			{
        		if(grandParent->right == NULL || grandParent->left == parent ) // uncle right
				{
            		if(grandParent->right->color == 0 && grandParent->right != NULL) 	//case 1 if parent and uncle (right) are red and son is red

					{
                		grandParent->right->color = 1;
                		parent->color = 1;
                		grandParent->color = 0;
                		proFix(grandParent);
                
            		}
            		else if(grandParent->right->color == 1 || grandParent->right == NULL) //cases(2) left right w left left
            		{
            			if(strcmp(parent->key,newNode->key) >= 0) //case left left
            			{
            				rotateRight(grandParent);
            				grandParent->color = !grandParent->color;
            				parent->color = !parent->color;
            				proFix(grandParent);
						}
						else //case left right
						{
							rotateLeft(parent);  //parent
							rotateRight(grandParent);
							grandParent->color = !grandParent->color;
            				parent->color = !parent->color;
            				proFix(grandParent);
						}
					}
        		}
        		else if(grandParent->right == parent)
				{
					if(grandParent->left->color == 0 && grandParent->left != NULL) 	//case 1 if parent and uncle(left) are red and son is red

					{
						grandParent->left->color = 1;
						parent->color = 1;
						grandParent->color = 0;
						proFix(grandParent);
					}
					else if(grandParent->left->color == 1 || grandParent->left == NULL) //cases(2) right left w right right
					{
						if(strcmp(parent->key,newNode->key) <= 0) //case right right
						{
							rotateLeft(grandParent);
							grandParent->color = !grandParent->color;
							parent->color = !parent->color;
							proFix(grandParent);
						}
						else //case right left
						{
							rotateRight(parent);
							rotateLeft(grandParent);
							grandParent->color = !grandParent->color;
							parent->color = !parent->color;
							proFix(grandParent);
						}
					}
        			
				}
    		}
		}
	}
	else 
	{
		newNode->color = 1;
	}
    
}



node * insertion(node *root,char data[])
{
    node  *temp = root;
    node *newNode;
    if(root==NULL)
    {
        root = createNode(data, NULL);
        root->color = 1;

        return root;

    }
    else
    {
		
        while(temp!=NULL)
        {
            if(strcmp(temp->key,data)>0)
            {
                if(temp->left==NULL)
                {
                    newNode = createNode(data,temp);
                    root->left=newNode;
					
                    break;
                }

                else
                    temp = temp->left;

            }

            else if(strcmp(temp->key,data)<0)
            {

                if(temp->right==NULL)
                {
                    newNode = createNode(data,temp);
                    root->right=newNode;
                    break;
                }
                else
                    temp = temp->right;

            }
        }
        //proFix(newNode);

    }
    
    cout<<newNode->key<<endl;
	

    //we call fix function after each insertion to maintain the RBT properties
}


int sizeOfTree(node *root)
{
	printf("size");
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
	printf("height");
    return (root == NULL) ? 0 :
           1+ MAX(height(root->left), height(root->right));
}
int search(node *root, char d[])
{
    if (root == NULL)
        return 0;
    else if (strcmp(d,root->key)==0)
        return 1;
    else if (strcmp(d,root->key)<0)
        return search(root->left, d);
    else
        return search(root->right, d);
}

void inorder(struct node *root)
{
	printf("inorder");
    if (root != NULL)
    {
        inorder(root->left);
        cout<<root->key<<" color: "<<root->color<<endl;

        inorder(root->right);
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
    const char d[2] = " ";
    char *token;


    node *root = NULL;



    //inserting first word in the root




    fgets (Word, 50, fp);
    root = insertion(root,Word);
	printf("%s\n",root->key);

    //inserting the rest of the tree
    while(!feof(fp))
    {

        fgets (Word, 50, fp);
        node *news = insertion(root,Word);
        printf("%s\n",news->key);

    }

	//inorder(root);


    //making sure its working

    printf("The size of the tree: %d\n",sizeOfTree(root));
    printf("The height of the tree:%d\n",height(root));

    while(1)
    {
        //getting input from user and putting in a tokenizer and making delimiter space
        gets(str);
        token= strtok(str,d);

        while(token)
        {
            if(search(root,token)==1)
            {
                printf("\nFound:%s\n",token);
                //getting the rest of the tokens
                token = strtok(NULL, d);
            }

            else
            {
                printf("\nCould not find:%s\n",token);


                token = strtok(NULL, d);

            }
        }
    }

    return 0;
}
