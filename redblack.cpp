#include <bits/stdc++.h> 

using namespace std;

class node { public: int data; node* left; node* right; node* prev; int l; int r; int count; bool color; char s; node(int x,bool a,node* p,char c){ data=x; left=NULL; right=NULL; prev=p; color=a; l=0; r=0; count=1; s=c; }

};

node* mainroot=NULL;

void Preorder(node* root){

if(root==NULL) return;

//cout<root.data<<" "<count<<endl; Preorder(root->left); Preorder(root->right);

}

void check(node* a) {

node* temp=(a->prev)->prev;
if( temp->left==NULL || temp->right==NULL || (temp->left)->color==false ||  (temp->right)->color==false )
{
  if((temp->left)==NULL || (temp->left)->color==false )
  {
      node* temp2=temp->right;

      if((temp2->left)==NULL || ( temp2->left)->color==false )
      {
          temp->right=temp2->left;
          temp->color=true;
          temp->r=temp2->l;
          temp2->l=temp->r+temp->l+1;

          temp2->left=temp;
          temp2->color=false;
          temp2->prev=temp->prev;

          temp->prev=temp2;

          if(temp2->prev!=NULL){
          if ( ( (temp2->prev)->left!=NULL) && (temp2->prev)->left==temp )
          (temp2->prev)->left=temp2;

          else
          (temp2->prev)->right=temp2;

          }

          else
          mainroot=temp2;

          temp2->s=temp->s;
          temp->s='l';

          if(temp->right!=NULL)
          (temp->right)->s='r';
      }
      else
      {
          node* rig=temp->right;

          temp->right=a->left;
          a->left=temp;
          a->prev=temp->prev;
          temp->prev=a;

          rig->left=a->right;
          a->right=rig;
          rig->prev=a;
          rig->l=a->r;
           temp->r=a->l;
          a->l=temp->l+temp->r+1;
           a->r=rig->l+rig->r+1;

          rig->color=true;
          a->color=false;
          temp->color=true;
          if(temp->left!=NULL)
          temp->left->color=false;

          if((a->prev)!=NULL)
          {
           if(((a->prev)->left)!=NULL && (a->prev)->left==temp )
           (a->prev)->left=a;

           else
           (a->prev)->right=a;
          }
          else
          mainroot=a;

          a->s=temp->s;

          if(rig->left!=NULL)
          (rig->left)->s='l';

          if(temp->right!=NULL)
          (temp->right)->s='r';
          temp->s='l';
      }

    }
    else
    {
        if((temp->left->right)==NULL || (temp->left->right)->color==false)
        {

            node* lef=temp->left;
            temp->left=lef->right;
            lef->right=temp;

            lef->prev=temp->prev;

            if(lef->prev==NULL)
            mainroot=lef;
            else
            {
              if( (lef->prev)->left!=NULL && (lef->prev)->left==temp )
              (lef->prev)->left=lef;
              else
              (lef->prev)->right=lef;
            }

            temp->l=lef->r;
            lef->r=temp->l+temp->r+1;
            temp->prev=lef;
            temp->color=true;
            lef->color=false;

            lef->s=temp->s;
            temp->s='r';
            if(temp->left!=NULL)
            (temp->left)->s='l';

        }

        else
        {
            node* lef=temp->left;
            temp->left=a->right;
            lef->right=a->left;
            a->left=lef;
            a->right=temp;
            a->prev=temp->prev;
            temp->prev=a;
            lef->prev=a;
            a->color=false;
            temp->color=true;


            if(a->prev!=NULL)
            { if( (a->prev)->left!=NULL && (a->prev)->left==temp )
              (a->prev)->left=a;
              else
              (a->prev)->right=a;
            }

            else
            mainroot=a;

            lef->r=a->l;
            temp->l=a->r;
            a->l=lef->l+lef->r+1;
            a->r=temp->l+temp->r+1;


            a->s=temp->s;
            temp->s='r';
            if(lef->right!=NULL)
            (lef->right)->s='r';

            if(temp->left!=NULL)
            (temp->left)->s='l';
        }



    }

}
else
{

   node* sec=a->prev;
   sec->color=false;
   (sec->prev)->color=true;
   node* lef=sec->prev->left;
   node* rig=sec->prev->right;
   lef->color=false;
   rig->color=false;

    if(temp->prev==NULL)
    temp->color=false;
    else
    {  if((temp->prev)->color==true)
       check(temp);
    }
}

}

int cgreat(node* root,int x,char c) { if(root==NULL) return 0;

if((root->data<x) && c=='f') return(cgreat(root->right,x,'f')); else if(root->data<x) return 0;

if((root->data)>=x) return(root->count+root->r+cgreat(root->left,x,'t'));

}

node* exactsearch(int key,node* root,int closest,node* refr) { if(root==NULL) return refr;

int z=(root)->data;

if(z==key)
return root;

if(z<key)
{   if(abs(closest-key)> abs(z-key))
    {closest=z;
     refr=root;
    }
    return(exactsearch(key,root->right,closest,refr));
}
if(z>key)
{
   if(abs(closest-key)> abs(z-key))
   {closest=z;
    refr=root;
   }
   return(exactsearch(key,root->left,closest,refr));
}

}

void rearrange(node* root,char c) {

if(root->color==true) { if(c=='r') {

    node* lef=root->left;

    if(lef->right!=NULL && (lef->right)->color==true)
     {
             node* temp2=(lef->right);

             temp2->prev=root->prev;     // as root is red its previous cannot be null

             if(root->s=='r')
             (temp2->prev)->right=temp2;
             else
             (temp2->prev)->left=temp2;

             lef->right=temp2->left;
             root->left=temp2->right;
             temp2->left=lef;
             lef->prev=temp2;
             temp2->right=root;
             root->prev=temp2;
             lef->r=temp2->l;
             root->l=temp2->r;

             temp2->l=lef->l+lef->r+1;
             temp2->r=root->l+root->r+1;
             swap(root->s,temp2->s);

              if(lef->right!=NULL)
             {
               (lef->right)->s='r';
               (lef->right)->prev=lef;
             }

              if(root->left!=NULL)
              {
                (root->left)->s='l';

                (root->left)->prev=root;

              }


               temp2->color=true;
               root->color=false;
               lef->color=false;

               while((temp2->prev)!=NULL)
            {
               if(temp2->s=='l')
               {
                 ((temp2->prev)->l)--;
               }
               else
               {
                 ((temp2->prev)->r)--;
               }
               temp2=temp2->prev;

            }
            return;

     }

     if(lef->left!=NULL && (lef->left)->color==true)
     {

         node* lef=root->left;
         node* temp2=lef->left;

         if(root->s=='r')
         {
             (root->prev)->right=lef;
         }
         else
         {
             (root->prev)->left=lef;
         }

         lef->color=true;
         temp2->color=false;
         root->color=false;

         lef->prev=root->prev;
         lef->s=root->s;
         root->left=lef->right;
         lef->right=root;
         root->prev=lef;
         root->s='r';

         if(root->left!=NULL)
         {(root->left)->s='l';
           (root->left)->prev=root;
         }
         root->l=lef->r;
         lef->r=root->r+root->l+1;

             while((lef->prev)!=NULL)
            {
               if(lef->s=='l')
               {
                 ((lef->prev)->l)--;
               }
               else
               {
                 ((lef->prev)->r)--;
               }
               lef=lef->prev;

            }

         return;
     }

     if(1)  // when both child of lef are black
     {
         root->color=false;
         (root->left)->color=true;
         while((root->prev)!=NULL)
            {
               if(root->s=='l')
               {
                 ((root->prev)->l)--;
               }
               else
               {
                 ((root->prev)->r)--;
               }
               root=root->prev;

            }

         return;
     }
 }
 else
 {
     node* rig=root->right;



     if(rig->left!=NULL && (rig->left)->color==true)
     {


         node* temp=rig->left;

         if(root->s=='r')
         {

             (root->prev)->right=temp;
         }
         else
         (root->prev)->left=temp;

         temp->prev=root->prev;
         temp->s=root->s;
         root->right=temp->left;
         rig->left=temp->right;


         if(rig->left!=NULL)
      {
          (rig->left)->s='l';
          (rig->left)->prev=rig;
      }

         if(root->right!=NULL)
        {
          (root->right)->s='r';
          (root->right)->prev=root;
        }


         temp->left=root;
         temp->right=rig;

         root->prev=temp;
         rig->prev=temp;
         root->s='l';

         rig->l=temp->r ;
         root->r=temp->l ;

         temp->l=root->r +root->l +1;

         temp->r=rig->l +rig->r +1;

         temp->color=true;
         root->color=false;
         rig->color=false;




         while((temp->prev)!=NULL)
         {
               if(temp->s=='l')
               {
                 ((temp->prev)->l)--;
               }
               else
               {
                 ((temp->prev)->r)--;
               }
               temp=temp->prev;

        }


      return;
     }


     if(rig->right!=NULL && (rig->right)->color==true)
     {

         node* rig=root->right;
         node* temp2=rig->right;

         if(root->s=='r')
         {
             (root->prev)->right=rig;
         }
         else
         {
             (root->prev)->left=rig;
         }



         rig->prev=root->prev;
         rig->s=root->s;
         root->right=rig->left;
         rig->left=root;
         root->prev=rig;
         root->s='l';

         if(root->right!=NULL)
         {
             (root->right)->s='l';
            (root->right)->prev=root;

         }
         root->r=rig->l;
         root->s='l';
         rig->l=root->r+root->l+1;

             while((rig->prev)!=NULL)
            {
               if(rig->s=='l')
               {
                 ((rig->prev)->l)--;
               }
               else
               {
                 ((rig->prev)->r)--;
               }
               rig=rig->prev;

            }

         return;

    }

     if(1)
     {
         //when leaf is black

         root->color=false;
         (root->right)->color=true;
         while((root->prev)!=NULL)
            {
               if(root->s=='l')
               {
                 ((root->prev)->l)--;
               }
               else
               {
                 ((root->prev)->r)--;
               }
               root=root->prev;

            }



         return;


     }


 }

} else { node* temp=root->left; node* temp2=root->right;

 if(c=='r' && temp->color==false )
 {
     node* lef=temp->left;
     node* rig=temp->right;


     if((rig==NULL && lef==NULL) || ( (rig!=NULL && rig->color==false) && (lef!=NULL && lef->color==false) ) )
     {
          temp->color=true;
          if(root->prev==NULL)
          return;
          else
          {
              if(root->s=='l')
              {
               ((root->prev)->l)--;
                rearrange(root->prev,'l');

              }
              else
              {
                 ((root->prev)->r)--;
                rearrange(root->prev,'r');

              }
          }
          return;
     }


     if(rig!=NULL && rig->color==true)
     {

        temp->right=rig->left;

        temp->r=rig->l;

        root->left=rig->right;

        root->l=rig->r;

                                                     //  rig
        rig->prev=root->prev;

                                                // temp   found
        if(root->s=='r')
        (rig->prev)->right=rig;

        else if(root->s=='l')
        (rig->prev)->left=rig;
        else
        mainroot=rig;

         rig->left=temp;
         rig->right=root;

         temp->prev=rig;
         root->prev=rig;


         rig->s=root->s;
         temp->s='l';

         root->s='r';


         rig->color=false;

         rig->l=1+temp->l+temp->r;
         rig->r=1+root->l+root->r;


          if(temp->right!=NULL){
         (temp->right)->s='r';
         (temp->right)->prev=temp;
          }

          if(root->left!=NULL){
         (root->left)->s='l';
         (root->left)->prev=root;
          }

          while(rig->prev!=NULL)
          {
              if(rig->s=='l')
               {
                 ((rig->prev)->l)--;
               }
               else
               {
                 ((rig->prev)->r)--;
               }
               rig=rig->prev;

          }



        return;
     }

     if(lef->color==true)
     {

        temp->prev=root->prev;
        temp->s=root->s;

        if(root->s=='l')
        (temp->prev)->left=temp;

        else if(root->s=='r')
        (temp->prev)->right=temp;
         else
         mainroot=temp;

        root->left=temp->right;
        root->l=temp->r;

        if(root->left!=NULL){
        (root->left)->s='l';
        (root->left)->prev=root;
        }
        root->prev=temp;
        root->s='r';

        temp->right=root;
        temp->r=1+root->l+root->r;

        lef->color=false;


         while((temp->prev)!=NULL)
            {
               if(temp->s=='l')
               {
                 ((temp->prev)->l)--;
               }
               else
               {
                 ((temp->prev)->r)--;
               }
               temp=temp->prev;

            }


        return ;
     }


 }

 if(c=='l' && (root->right)->color==false)
 {

     node* lef1=temp2->left;
    node* rig1=temp2->right;

     if( (rig1==NULL && lef1==NULL) || ( (rig1!=NULL && rig1->color==false) && ( (lef1!=NULL) && lef1->color==false) ) )
     {

         temp2->color=true;
          if(root->prev==NULL)
          return;
          else
          {
              if(root->s=='l')
              {
               ((root->prev)->l)--;
                rearrange(root->prev,'l');

              }
              else
              {
                 ((root->prev)->r)--;
                rearrange(root->prev,'r');

              }
          }

      return;
     }


  if(lef1!=NULL && lef1->color==true)
  {
       temp2->left=lef1->right;

        temp2->l=lef1->r;

        root->right=lef1->left;

        root->r=lef1->l;

                                                     //  rig
        lef1->prev=root->prev;

                                                // temp   found
        if(root->s=='r')
        (lef1->prev)->right=lef1;

        else if(root->s=='l')
        (lef1->prev)->left=lef1;
         else
         mainroot=lef1;

         lef1->left=root;
         lef1->right=temp2;

         temp2->prev=lef1;
         root->prev=lef1;


         lef1->s=root->s;
         temp2->s='r';

         root->s='l';


         lef1->color=false;

         lef1->r=1+temp2->l+temp2->r;
         lef1->l=1+root->l+root->r;


         if(temp2->left!=NULL){
         (temp2->left)->s='l';
         (temp2->left)->prev=temp2;
         }

         if(root->right!=NULL){
         (root->right)->s='r';
         (root->right)->prev=root;
         }

          while(lef1->prev!=NULL)
          {
              if(lef1->s=='l')
               {
                 ((lef1->prev)->l)--;
               }
               else
               {
                 ((lef1->prev)->r)--;
               }
               lef1=lef1->prev;

          }



        return;

    }

    if(rig1->color==true)
    {
         temp2->prev=root->prev;
         temp2->s=root->s;

        rig1->color=false;
        if(root->s=='l')
        (temp2->prev)->left=temp2;

         else if(root->s=='r')
        (temp2->prev)->right=temp2;
         else
         mainroot=temp2;

        root->right=temp2->left;
        root->r=temp2->l;


         if(root->right!=NULL){
        (root->right)->s='r';
        (root->right)->prev=root;
         }
        root->prev=temp2;
        root->s='l';

        temp2->left=root;
        temp2->l=1+root->l+root->r;


          while((temp2->prev)!=NULL)
            {
               if(temp2->s=='l')
               {
                 ((temp2->prev)->l)--;
               }
               else
               {
                 ((temp2->prev)->r)--;
               }
               temp2=temp2->prev;

            }

       return ;


    }



 }


 if(c=='r' && (root->left)->color==true)
 {
     node* le=root->left;
     node* re1=le->right;

     node* c1=re1->left;
     node* d=re1->right;


     if( ( c1==NULL && d==NULL ) || ( c1!=NULL && c1->color==false && d->color==false) )
     {

         le->prev=root->prev;

         if(root->s=='r')
         (le->prev)->right=le;

         else if(root->s=='l')
         (le->prev)->left=le;
          else
          mainroot=le;

         le->s=root->s;

         le->right=root;
         root->prev=le;

         root->left=re1;
         root->s='r';

         root->l=re1->l+re1->r+1;

         re1->prev=root;
         re1->s='l';

         le->r=root->l+root->r+1;


          le->color=false;
          re1->color=true;




          while((le->prev)!=NULL)
            {
               if(le->s=='l')
               {
                 ((le->prev)->l)--;
               }
               else
               {
                 ((le->prev)->r)--;
               }
               le=le->prev;

            }


          return;


     }

     else
     {

         if(c1!=NULL && c1->color==true)
         {

             re1->prev=root->prev;

             if(root->s=='r')
             (re1->prev)->right=re1;
             else if(root->s=='l')
             {
                 (re1->prev)->left=re1;
             }
              else
              mainroot=re1;

             re1->s=root->s;

             le->right=c1;

             le->prev=re1;

             c1->prev=le;
             c1->s='r';

             le->r=re1->l;

             re1->left=le;

             root->left=re1->right;

             re1->right=root;


             root->prev=re1;

             root->s='r';

             c1->color=false;

             if(root->left!=NULL)
             {(root->left)->s='l';
              (root->left)->prev=root;
             }

             c1->s='r';



             root->l=re1->r;

             re1->l=1+le->l+le->r;
             re1->r=1+root->l+root->r;



          while((re1->prev)!=NULL)
            {
               if(re1->s=='l')
               {
                 ((re1->prev)->l)--;
               }
               else
               {
                 ((re1->prev)->r)--;
               }
               re1=re1->prev;

            }

             return;
         }

         else
         {
                  //  d

                d->prev=root->prev;

                if(root->s=='r')
                (root->prev)->right=d;
                else if(root->s=='l')
                (root->prev)->left=d;
                else
                mainroot=d;


                d->s=root->s;
                d->color=false;
                re1->right=d->left;

                if(re1->right!=NULL){

                (re1->right)->prev=re1;
                (re1->right)->s='r';

                }

                 re1->r=d->l;

                  root->left=d->right;

                  if(root->left!=NULL){
                  (root->left)->prev=root;
                  root->left->s='l';
                  }
                  (root->l)=d->r;

                  le->r=1+re1->l+re1->r;

                  d->left=le;
                  d->right=root;

                  d->l=1+le->l+le->r;
                  d->r=1+root->l+root->r;

                  le->prev=d;
                  root->prev=d;

              while((d->prev)!=NULL)
            {
               if(d->s=='l')
               {
                 ((d->prev)->l)--;
               }
               else
               {
                 ((d->prev)->r)--;
               }
               d=d->prev;

            }
          return;
         }
     }

 }


 if(c=='l'  && (root->right)->color==true)
 {

     node* re=root->right;
     node* le1=re->left;


     node* a=le1->left;
     node* b=le1->right;



      if( ( a==NULL && b==NULL ) || ( a!=NULL && a->color==false && b->color==false ) )
     {

         re->prev=root->prev;

         if(root->s=='r')
         (re->prev)->right=re;

         else if(root->s=='l')
         (re->prev)->left=re;
         else
         mainroot=re;

         re->s=root->s;

         re->left=root;
         root->prev=re;              //  done

         root->right=le1;
         root->s='l';

         root->r=le1->l+le1->r+1;

         le1->prev=root;
         le1->s='r';

         re->l=root->l+root->r+1;


          re->color=false;
          le1->color=true;


          while((re->prev)!=NULL)
            {
               if(re->s=='l')
               {
                 ((re->prev)->l)--;
               }
               else
               {
                 ((re->prev)->r)--;
               }
               re=re->prev;

            }


       return;

    }
    else
    {
        if(a!=NULL && a->color==true)
        {


            a->prev=root->prev;

            if(root->s=='r')
            (a->prev)->right=a;

            else if(root->s=='l')
            (a->prev)->left=a;
            else
            mainroot=a;


            a->s=root->s;

            le1->left=a->right;
            le1->l=a->r;

            if(le1->left!=NULL)
            {(le1->left)->s='l';
            (le1->left)->prev=le1;
            }

            root->right=a->left;
            root->r=a->l;

            if(root->right!=NULL)
           {
             (root->right)->s='r';
            (root->right)->prev=root;
           }

            a->right=re;
            a->left=root;

            root->s='l';

            root->prev=a;
            re->prev=a;

            a->color=false;

            re->l=1+le1->l+le1->r;

            a->l=root->l+root->r+1;
            a->r=re->l+re->r+1;

            while((a->prev)!=NULL)
            {
               if(a->s=='l')
               {
                 ((a->prev)->l)--;
               }
               else
               {
                 ((a->prev)->r)--;
               }
               a=a->prev;

            }

           return;
        }

        if(b!=NULL && b->color==true)
        {
           le1->prev=root->prev;

           if(root->s=='r')
           (le1->prev)->right=le1;
           else if(root->s=='l')
           (le1->prev)->left=le1;
            else
            mainroot=le1;

           le1->s=root->s;

           root->right=le1->left;
           root->r=le1->l;

           if((root->right)!=NULL)
           {  (root->right)->s='r';
              (root->right)->prev=root;
           }

           re->left=b;
           re->l=le1->r;
           (b)->s='l';
           b->prev=re;

           le1->left=root;
           root->prev=le1;

           le1->right=re;
           re->prev=le1;

           root->s='l';

            le1->l=1+root->l+root->r;
            le1->r=1+re->l+re->r;

            while((le1->prev)!=NULL)
            {
               if(le1->s=='l')
               {
                 ((le1->prev)->l)--;
               }
               else
               {
                 ((le1->prev)->r)--;
               }
               le1=le1->prev;

            }


           return;


        }


    }


 }

}

}

int del(node* root,int key) {

node* found=exactsearch(key,root,root->data,root);

if( (found->data)!=key)
{
  return(found->data);
}
else
{  if((found->count)>1)
   {
       (found->count)--;
       return key;
   }
  if((found)->left == NULL  && (found)->right==NULL)
  {
      if(found->color==true)
      {
         node* temp=found->prev;

         if(found->s=='l')
         {(temp)->left=NULL;
           temp->l=0;
         }
         else
         {(temp)->right=NULL;
           temp->r=0;
         }
         while((temp->prev)!=NULL)
         {
             if(temp->s=='l')
             {
                 ((temp->prev)->l)--;       //  red leaf
             }
             else
             {
                 ((temp->prev)->r)--;
             }
             temp=temp->prev;

         }

         //Preorder(mainroot);
          delete(found);
         return(key);
      }
      else
      {
       //leaf is black


       node* temp=found->prev;
       if(temp==NULL)
       {   mainroot=NULL;
           delete(found);
           return key;
       }
       if(found->s=='l')
       {  delete(found);
          temp->left=NULL;
          (temp->l)--;
          rearrange(temp,'l');

       }
       else
       {
           delete(found);
           temp->right=NULL;
           (temp->r)--;

           rearrange(temp,'r');
       }

        return key;
       }


    }

  else
  {
    if((found->left)!=NULL && (found->right)==NULL )
    {

        node* lef=(found)->left;
        node* temp=found->prev;

        if(temp!=NULL){

        if(found->s=='r')
        { (temp)->right=lef;

           ((temp)->r)--;
        }
        else
        { (temp)->left=lef;

          ((temp)->l)--;
        }
        lef->prev=found->prev;
        lef->color=false;
        lef->s=found->s;

        while(temp->prev!=NULL)
        {
            if(temp->s=='r')
            ((temp->prev)->r)--;
            else
            ((temp->prev)->l)--;

            temp=temp->prev;
        }

         delete(found);
         return key;
        }
        else
        {
         mainroot=(found->left);
         lef->color=false;
         lef->prev=NULL;
         lef->s='n';
         delete(found);
         return key;
        }
  }

 else
 {
   if((found->left)==NULL && (found->right)!=NULL )
    {

        node* rig=(found)->right;
        node* temp=found->prev;
        if(temp!=NULL){

        if(found->s=='r')
        { (temp)->right=rig;

           ((temp)->r)--;
        }
        else
        { (temp)->left=rig;

          ((temp)->l)--;
        }
        rig->prev=found->prev;
        rig->color=false;
        rig->s=found->s;

        while(temp->prev!=NULL)
        {
            if(temp->s=='r')
            ((temp->prev)->r)--;
            else
            ((temp->prev)->l)--;

            temp=temp->prev;
        }

         delete(found);
         return key;
      }
      else
      {
          mainroot=(found->right);
          rig->prev=NULL;
          rig->color=false;
          rig->s='n';
          delete(found);
          return key;

      }

   }

   else
   {

   // when both children exist
    node* temp=found->left;

    while(temp->right!=NULL)
    temp=temp->right;

    swap(temp->data,found->data);

    del(temp,key);
    return key;
   }

     }

  }

}

} node* search(int key,node* root) { if(root==NULL) return root;

if(key==root->data)
return root;

if(key<(root->data))
return search(key,root->left);
else
return search(key,root->right);

}

void insert(node** root,int x,node* prev,char c) { if( (*root) == NULL) { if(prev==NULL) { *root=new node(x, false , prev,'n'); return;

}
else
{  *root=new node(x , true , prev,c);

   if(prev->color==true)
   check(*root);
   return;
}

}

if(x<=(*root)->data) { if((*root)->data==x) ((*root)->count)++; else{ ((*root)->l)++; insert( &((*root)->left) , x ,*root,'l'); } } else { ((*root)->r)++; insert( &((*root)->right) , x ,*root,'r'); } }

int maximum(node* root) { while(root->right!=NULL) root=root->right;

return(root->data);

}

int minimum(node* root) {

while(root->left!=NULL) root=root->left;

return root->data; }

int main() {

ifstream inFile;

inFile.open("C:/Users/Vaibhav/Desktop/codeb/rblack/fi.txt");

if (!inFile) { cout << "Unable to open file";

exit(1);

} int e,p; inFile>>e; while(e--) { inFile>>p; insert(&mainroot,p,NULL,'n'); }

int x,y,a,b,v,d;
int z=0;
node* f;
while(z==0){
cout<<"To insert press 1"<<endl<<"To find range enter 2"<<endl<<"To delete press 3"<<endl<<"To view all elements press 4"<<"\n"<<"For max press 5"<<endl<<"For min press 6"<<endl;
cin>>v;
switch(v)
{
    case 1: cout<<"Enter value to be inserted\n";
            cin>>x;
            insert(&mainroot,x,NULL,'n');        // insert
            break;

    case 2: if(mainroot!=NULL){
            cout<<"enter x enter y for range query\n";
            cin>>x;
            cin>>y;
            a=cgreat(mainroot,x,'f');
            b=cgreat(mainroot,y,'f');       //   range
            f=search(y,mainroot);
            if(f!=NULL && f->data==y)
            cout<<a-b+f->count<<endl;
            else
            cout<<a-b<<endl;}
            else
            cout<<"No element present cannot query\n";

            break;

   case 3:  if(mainroot!=NULL){
            cout<<"Enter the element to be deleted\n";
            cin>>x;
            d=del(mainroot,x);
            if(d==x)
            cout<<d<<" has been deleted\n";
            else
            cout<<x<<" is not present in database but element closest to it is "<<d<<endl;                                    // delete
            break;}
            else
            cout<<"No element present\n";
            break;
   case 4:    if(mainroot!=NULL)
              Preorder(mainroot);
              else
              cout<<"No element present\n";
              break;

   case 5:   if(mainroot!=NULL)
             cout<<maximum(mainroot)<<endl;
             else
             cout<<"No element present\n";
             break;
   case 6:     if(mainroot!=NULL)
               cout<<minimum(mainroot)<<endl;
               else
               cout<<"No element present\n";
            break;
}
cout<<"To enter more data enter 0 to leave press any other key";

cin>>z;
}

return 0;

}
