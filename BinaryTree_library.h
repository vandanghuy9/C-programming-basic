typedef struct
{
	char maCP[4];
	float gia_mo[10];
	float gia_dong[10];
}elementtype ;
typedef struct node
{
	elementtype data;
	struct node *left;
	struct node *right;
}node_t;
 
typedef node_t* TreeType;
 
void makenullTree(TreeType *t)
{
	(*t) = NULL;
}
 
elementtype inputData()
{
	elementtype tmp;
	printf("ma Cp:");
	scanf("%s",tmp.maCP);
	printf("Gia mo cua:");
	scanf("%f",&tmp.gia_mo);
	
	printf("Gia dong cua:");
	scanf("%f",&tmp.gia_dong);
	
	return tmp;
}
  	 
  	 
node_t *createnewNode(elementtype x)
{
	node_t *new;
	new = (node_t *)malloc(sizeof(node_t));
	if (new != NULL)
	{
    	new->data = x;
    	new->left = NULL;
    	new ->right = NULL;
	}
	return new;
}
 
int IsEmpty(TreeType t)
{
	return (t == NULL);
}
 
int IsLeaf(TreeType t)
{
	return (t->left == NULL && t->right == NULL);
}
 
TreeType InsertNode (TreeType t,elementtype x)
{
	if (IsEmpty(t))
	{
    	node_t *new;
    	new = (node_t *)malloc(sizeof(node_t));
    	new->data = x;
    	new ->left = NULL;
    	new-> right = NULL;
    	t = new;
	}
	else
	{
    	if (strcmp((t->data).maCP,x.maCP ) > 0) t->left = InsertNode(t->left , x);
    	else
    	{
        	if (strcmp((t->data).maCP,x.maCP ) < 0) t->right= InsertNode(t->right, x);
    	}
	}
	return t;
}
 
TreeType Search(TreeType t, elementtype find)
{
	if (IsEmpty(t))
	{
    	return NULL;
	}
	else
	{
    	if (strcmp(t->data.maCP,find.maCP)== 0) return t;
    	else
    	{
        	if (strcmp(t->data.maCP,find.maCP) < 0) return Search(t->right,find);
        	else return Search(t->left,find);
    	}
	}
}
 
int count_node(TreeType t)
{
	if (t == NULL) return 0;
	else
	{
    	int left = count_node(t->left);
    	int right = count_node(t->right);
    	return 1 + left +right;
	}
}
 
int count_leaf(TreeType t)
{
	int count = 0;
	if (t == NULL) return 0;
	if (t->right == NULL && t->left == NULL)return 1;
	else
	{
    	int ld= count_leaf(t->left);
    	int rd = count_leaf(t->right);
    	count += ld+rd;
	}
	return count;
}
 
int Height(TreeType t)
{
	int h =0;
	if (t == NULL)
	{
    	return 0;
	}
	else
	{
    	int ld = Height(t->left);
    	int rd = Height(t->right);
    	h = (ld > rd ? ld : rd);
    	return (1+h) ;
	}
}
 
int RightChild(TreeType t)
{
	if ( t == NULL ) return 0;
	else
	{
    	if (t -> right != NULL) return ( 1+ RightChild(t->left) + RightChild(t ->right));
    	else return RightChild(t->left);
	}
}

int Internal_Node(TreeType t)
{
	if (t == NULL ) return 0;
	else
	{
    	int nb_node = count_node(t);
    	int nb_leaf = count_leaf(t);
    	return (nb_node-nb_leaf);
	}
}
 
elementtype DeleteMin (TreeType *t)
{
	elementtype tmp;
	if ((*t)->left == NULL)
	{
    	tmp = (*t)->data;
    	(*t)=(*t) ->right;
    	return tmp;
	}
	else return DeleteMin(&(*t)->left);
}
void FreeNode(TreeType *t,elementtype x)
{
	if ((*t)!= NULL)
	{
    	if (strcmp((*t)->data.maCP,x.maCP) < 0) FreeNode(&(*t)->right,x);
    	else if (strcmp((*t)->data.maCP,x.maCP) > 0) FreeNode(&(*t)->left,x);
    	else if ((*t)->right == NULL && (*t)->left ==NULL)
    	{
        	free(*t);
        	(*t) = NULL;
    	}
    	else if ((*t)->left == NULL)
    	{
        	TreeType tmp = *t;
        	(*t)= (*t)->right;
        	free(tmp);
    	}
    	else if ((*t)->right == NULL)
    	{
        	TreeType tmp = (*t);
        	(*t)=(*t)->left;
        	free(tmp);
    	}
    	else
    	{
        	(*t)->data=DeleteMin(&(*t)->right);
    	}
	}
}
 
void BFS (TreeType t,int h)
{
	if (t == NULL)
	{
    	return ;
	}
	else
	{
    	if (h == 1) printf("%s\t%f\t%f\n",t->data.maCP,t->data.gia_mo,t->data.gia_dong);
    	else if (h > 1)
    	{
        	BFS(t->left,h-1);
        	BFS(t->right,h-1);
    	}
	}
 
}
void printBFS(TreeType t)
{
	int h = Height(t);
	int i;
	for (i=1;i<=h;i++)
	{
    	BFS(t,i);
	}
}
 
 
void Preorder(TreeType t)
{
	if (t != NULL)
	{
    	printf("%s\t%f\t%f\n",t->data.maCP,t->data.gia_mo,t->data.gia_dong);
    	Preorder(t->left);
    	Preorder(t->right);
	}
   
}
void Inorder(TreeType t)
{
	if (t != NULL)
	{
    	Inorder(t->left);
    	printf("%s\t%f\t%f\n",t->data.maCP,t->data.gia_mo[0],t->data.gia_dong[0]);
    	Inorder(t->right);
	}
   
}
 
void Postorder(TreeType t)
{
	if (t != NULL)
	{
    	Postorder(t->left);
    	Postorder(t->right);
     	printf("%s\t%f\t%f\n",t->data.maCP,t->data.gia_mo,t->data.gia_dong);
	}
   
}
 
void FreeTree(TreeType t)
{
   if (t != NULL)
   {
   	FreeTree(t->left);
   	FreeTree(t->right);
   	free((void *)t);
   }
}
 
void savetoArray(TreeType t, elementtype list[],int *count)
{  
	if (t != NULL)
	{
   	savetoArray(t->left, list,count);
   	list[(*count)] = t->data;
   	(*count) +=1;
   	savetoArray(t->right, list,count);
	}
}
void Savefile(FILE *fi,TreeType t)
{
  if (t != NULL)
	{
  	Savefile(fi,t->left);
  	printf("%s\t%f\t%f\n",t->data.maCP,t->data.gia_mo,t->data.gia_dong);
  	Savefile(fi,t->right);
	}
}

void Matang(TreeType t)
{
	if (t != NULL)
	
	{
		Matang(t->left);
		int i;
		if (t->data.gia_mo[0] < t->data.gia_dong[0] && t->data.gia_mo[1] < t->data.gia_dong[1])
		{
			printf("%-16s%-16.3f%-16.3f\n",t->data.maCP,t->data.gia_mo[0],t->data.gia_dong[0]);
			printf("%-16s%-16.3f%-16.3f\n",t->data.maCP,t->data.gia_mo[1],t->data.gia_dong[1]);
		}
		Matang(t->right);
	}
}