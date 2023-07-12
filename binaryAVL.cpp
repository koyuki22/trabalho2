#include<iostream>
using namespace std;
struct avl {
	int info;
	struct avl *esq;
	struct avl *dir;
};
avl *raiz = NULL;
int height(avl *t) {
	int h = 0;
	if (t != NULL) {
		int l_height = height(t->esq);
		int r_height = height(t->dir);
		int max_height = max(l_height, r_height);
		h = max_height + 1;
	}
	return h;
}
int difference(avl *t) {
	int l_height = height(t->esq);
	int r_height = height(t->dir);
	int b_factor = l_height - r_height;
	return b_factor;
}
avl *rr_rotat(avl *parent) {
	avl *t;
	t = parent->dir;
	parent->dir = t->esq;
	t->esq = parent;
	cout<<"Right-Right Rotation" << endl;
	return t;
}
avl *ll_rotat(avl *parent) {
	avl *t;
	t = parent->esq;
	parent->esq = t->dir;
	t->dir = parent;
	cout<<"Left-Left Rotation"<< endl;
	return t;
}
avl *lr_rotat(avl *parent) {
	avl *t;
	t = parent->esq;
	parent->esq = rr_rotat(t);
	cout<<"Left-Right Rotation"<< endl;
	return ll_rotat(parent);
}
avl *rl_rotat(avl *parent) {
	avl *t;
	t = parent->dir;
	parent->dir = ll_rotat(t);
	cout<<"Right-Left Rotation"<< endl;
	return rr_rotat(parent);
}
avl *balance(avl *t) {
	int bal_factor = difference(t);
	if (bal_factor > 1) {
		if (difference(t->esq) > 0)
			t = ll_rotat(t);
		else
			t = lr_rotat(t);
	} else if (bal_factor < -1) {
		if (difference(t->dir) > 0)
			t = rl_rotat(t);
		else
			t = rr_rotat(t);
	}
	return t;
}
avl *insert(avl *r, int v) {
	if (r == NULL) {
		r = new avl;
		r->info = v;
		r->esq = NULL;
		r->dir = NULL;
		return r;
	} else if (v< r->info) {
		r->esq = insert(r->esq, v);
		r = balance(r);
	} else if (v >= r->info) {
		r->dir = insert(r->dir, v);
		r = balance(r);
	}
	return r;
}
void show(avl *p, int l) {
	int i;
	if (p != NULL) {
		show(p->dir, l+ 1);
		cout<<" ";
		if (p == raiz)
			cout << " R.";
		for (i = 0; i < l&& p != raiz; i++)
			cout << ".";
		cout << p->info;
		show(p->esq, l + 1);
	}
}
void inorder(avl *t) {
	if (t == NULL)
		return;
	inorder(t->esq);
	cout << t->info << " ";
	inorder(t->dir);
}
bool consultaNaArvore(int n) {
	avl *aux;
	if(raiz == NULL) {
		cout << "Arvore Vazia!!" << endl;
		return false;
	} else {
		aux = raiz;
		cout << "Procurando";
		/*enquanto aux não apontar para NULL será feita uma busca na árvore*/
		while(aux != NULL) {
			cout << ".";
			if(aux->info == n) {
				cout << endl;
				return true; /* achou! */
			} else if(n < aux->info) aux = aux->esq;
			else aux = aux->dir;
		}
		cout << endl;
		return false;
	}
}
avl * removeDaArvore(avl *r, int x) {
	avl *p;
	if(r == NULL) {
		return NULL;
	} else if(x > r->info) {
		r->dir = removeDaArvore(r->dir,x);
		r = balance(r);
	} else if(x < r->info) {
		r->esq = removeDaArvore(r->esq,x);
		r = balance(r);
	} else {
		if(r->dir != NULL) {
			p = r->dir;
			while(p->esq != NULL) {
				p = p->esq;
			}
			r->info = p->info;
			r->dir = removeDaArvore(r->dir,p->info);
			r = balance(r);
		} else
			return(r->esq);
	}
	return(r);
}
int main() {
	int c, n;
	do {
		cout << "1. Inserir" << endl;
		cout << "2. Mostrar arvore" << endl;
		cout << "3. Mostrar elementos em ordem" << endl;
		cout << "4. Pesquisar" << endl;
		cout << "5. Deletar" << endl;
		cout << "6. Sair" << endl;
		cout << "Escolha a opcao: ";
		cin >> c;
		if (c==1) {
			cout << "Valor para inserir: ";
			cin >> n;
			raiz = insert(raiz, n);
		}
		if (c==2) {
			if (raiz == NULL) {
				cout << "Arvore vazia" << endl;
				continue;
			}
			cout << "Arvore AVL Balanceada:" << endl;
			show(raiz, 1);
			cout<<endl;
		}
		if (c==3) {
			cout << "Elementos em ordem:" << endl;
			inorder(raiz);
			cout << endl;
		}
		if (c==4) {
			cout << "Elemento para pesquisar:" << endl;
			cin >> n;
			if (consultaNaArvore(n)) cout << "Achou!" << endl;
			else cout << "Nao Achou!" << endl;
		}
		if (c==5) {
			cout << "Elemento para Deletar:" << endl;
			cin >> n;
			raiz = removeDaArvore(raiz, n);
		}
	} while (c!=6);
}