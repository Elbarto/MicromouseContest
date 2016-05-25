from tkinter import *
from math import *
from time import *
from random import *


# dans variable murs : [bas, gauche, haut, droite, numero]


can = None;
cases = 9;
largeur_case=50;
marge = 10;
murs = [];
current_case = None;
visited=[];
arrivee=[];


########################################################################################################################################################################

#creation matrice avec cases*cases liste de [1,1,1,1, num de la case] 
# matrice [ligne][colonne]
#      2
#   _______
#   |     |
# 1 |     | 3
#   |_____|
#    
#      0
#

def init_gen():
    global cases, murs, current_case;
    current_case=0;
    
    for j in range(cases):
        li=[];
        for i in range(cases):
            struct=[1,1,1,1,j*cases+i];
            li.append(struct);
        murs.append(li);

def start():
    global current_case;
    current_case = 0;
    return 1;

def affiche_murs(murs):
    global cases;
    for i in range(cases):
        print(murs[i]);
    
def break_mur(pos, v_y, v_x):
    global murs, cases;
    for i in range(cases):
        for j in range(cases):
            if(murs[i][j][4]==pos):
                #trouve le mur à casser
                mur=abs(v_x)*(v_x+2)+abs(v_y)*(v_y+1);
                murs[i][j][mur]=0;
                #casse le mur complémentaire
                murs[i-v_y][j+v_x][(mur+2)%4]=0;
    
                    

def put_end():
    global murs, cases, arrivee, visited;
    x=randint(0,cases-5);
    y=randint(0,cases-5);
    num_arrivee = x+2 + cases*(y+2);
    for i in range(2):
        arrivee.append(num_arrivee+i);
        arrivee.append(num_arrivee+cases+i);
        visited.append(num_arrivee+i);
        visited.append(num_arrivee+cases+i);
    
    #on en enlève un pour pouvoir accéder à l'arrivée
    del visited[randint(0,3)];
    #on ajoute le 0 après avoir fait l'accès à l'arrivée
    visited.append(0);
    
    break_mur(num_arrivee, 0, 1); #case en haut (à droite de arrivée)
    break_mur(num_arrivee, -1, 0); #case à gauche (en bas de l'arrivée)
    break_mur(num_arrivee+1, -1, 0); #case à droite
    break_mur(num_arrivee+cases, 0, 1); #case en bas 

    
    
def maj_murs():
    global can, cases, marge, murs, current_case;
    can.create_rectangle(marge,marge,cases*largeur_case+marge,cases*largeur_case+marge, fill='#888888999');
    
    for colorcase in visited:
        can.create_rectangle(marge+largeur_case*(colorcase%cases),marge+largeur_case*int(colorcase/cases),marge+largeur_case*(colorcase%cases+1),marge+largeur_case*(int(colorcase/cases)+1), fill='#777222888');
    
    for i in range(cases):
        for j in range(cases):
            for cote in range(4):
                if(murs[i][j][cote]==1):
                    if(cote==0):
                        can.create_line(marge+largeur_case*j,marge+largeur_case*i+largeur_case,marge+largeur_case*j+largeur_case,marge+largeur_case*i+largeur_case,fill="black", width=4)#ligne du bas
                    if(cote==1):
                        can.create_line(marge+largeur_case*j,marge+largeur_case*i,marge+largeur_case*j,marge+largeur_case*i+largeur_case,fill="black", width=4)#ligne à gauche
                    if(cote==2):
                        can.create_line(marge+largeur_case*j,marge+largeur_case*i,marge+largeur_case*j+largeur_case,marge+largeur_case*i,fill="black", width=4)#ligne du haut
                    if(cote==3):
                        can.create_line(marge+largeur_case*j+largeur_case,marge+largeur_case*i,marge+largeur_case*j+largeur_case,marge+largeur_case*i+largeur_case,fill="black", width=4)#ligne à droite
    can.create_rectangle(marge,marge,largeur_case+marge-2,largeur_case+marge-2, fill='#555888999');


#Randmove effectue un random et met à 0 les coordonnées du vecteur_déplacement si case déja visitée, 
#Si possibilité de déplacement, il casse un mur en direction d'une case non visitée et change case_current
#Si pas de possibilité, il retourne -1
def randmove(vecteur):
    global visited, current_case;
    while(vecteur!=[0,0,0,0]):
        
        v_rand=randint(0,3);

        #random de la case suivante en mettant le vecteur à 0 sauf pour le déplacement voulu
        if(vecteur[v_rand]!=0):
            vecteur_bis=vecteur[:];
            if(v_rand==0):
                vecteur_bis[1]=0;
                vecteur_bis[2]=0;
                vecteur_bis[3]=0;
        
            elif (v_rand==1):
                vecteur_bis[0]=0;
                vecteur_bis[2]=0;
                vecteur_bis[3]=0;
                
            elif (v_rand==2):
                vecteur_bis[0]=0;
                vecteur_bis[1]=0;
                vecteur_bis[3]=0;
                
            elif (v_rand==3):
                vecteur_bis[0]=0;
                vecteur_bis[1]=0;
                vecteur_bis[2]=0;
            future_case=current_case+vecteur_bis[0]+vecteur_bis[1]+vecteur_bis[2]*cases+vecteur_bis[3]*cases;
            if(future_case in visited):
                vecteur[v_rand]=0; 
            else: 
                break_mur(current_case, -vecteur_bis[2]-vecteur_bis[3], vecteur_bis[0]+vecteur_bis[1]);
                return future_case;
    return -1

#Fonction raccordant le nouveau chemin à l'ancien en cassant un mur entre la current_case et une case visitée n'appartenant pas à l'arrivée
def randraccord():
    global visited, current_case, arrivee;
    vecteur=[-1,1,-1,1];#vecteur de déplacement : xa, xb, ya, yb
    
    if(current_case%cases==0):
        vecteur[0]=0;
    
    elif(current_case%cases==cases-1):
        vecteur[1]=0;
        
    if(current_case<cases):
        vecteur[2]=0;
    
    elif(current_case>cases*(cases-1)-1):
        vecteur[3]=0;
    
    v_rand=randint(0,3);
    while(vecteur[v_rand]==0):
        v_rand=randint(0,3);

    
    future_case=1000;
    while(future_case not in visited or future_case in arrivee):
        vecteur_bis=vecteur[:];
        if(v_rand==0):
            vecteur_bis[1]=0;
            vecteur_bis[2]=0;
            vecteur_bis[3]=0;
    
        elif (v_rand==1):
            vecteur_bis[0]=0;
            vecteur_bis[2]=0;
            vecteur_bis[3]=0;
            
        elif (v_rand==2):
            vecteur_bis[0]=0;
            vecteur_bis[1]=0;
            vecteur_bis[3]=0;
            
        elif (v_rand==3):
            vecteur_bis[0]=0;
            vecteur_bis[1]=0;
            vecteur_bis[2]=0;
        future_case=current_case+vecteur_bis[0]+vecteur_bis[1]+vecteur_bis[2]*cases+vecteur_bis[3]*cases;
        v_rand=randint(0,3);
    
    break_mur(current_case, -vecteur_bis[2]-vecteur_bis[3], vecteur_bis[0]+vecteur_bis[1]);


def move():
    global cases, murs, visited, current_case, arrivee;
    vecteur=[-1,1,-1,1];#vecteur de déplacement : xa, xb, ya, yb
    
    if(current_case%cases==0):
        vecteur[0]=0;
    
    elif(current_case%cases==cases-1):
        vecteur[1]=0;
        
    if(current_case<cases):
        vecteur[2]=0;
    
    elif(current_case>cases*(cases-1)-1):
        vecteur[3]=0;

    
    
    #random du déplacement
    v_move=randmove(vecteur);
    if(v_move!=-1):
        current_case = v_move;
        visited.append(current_case);
        
        maj_murs();

    #Il n'existe pas de déplacement non-visité possible, on repart d'une autre case
    else:
        i=0;
        while(i<cases*cases):
            if(i in visited):
                i=i+1;
            else:
                current_case = i;
                randraccord();
                visited.append(current_case);
                maj_murs();
                break
    if(len(visited)==cases*cases):
        return 1
        
    
    
def auto():
    a=move();
    while(a!=1):
        a=move(); 
    return 1
    
    
    
    
    
    
##########################################################################################################################################################    


init_gen();

fen = Tk();
can = Canvas(fen, width=cases*largeur_case+2*marge, height=cases*largeur_case+2*marge);
can.grid(row=0, column=0);

#but1=Button(fen, text="Auto", command=auto);
#but1.grid(row=1, column=0);

#but2=Button(fen, text="Next", command=move);
#but2.grid(row=2, column=0);







put_end();
maj_murs();

auto()   
   
    
#fen.mainloop()
    


    
#Pour avoir la partie graphique :
# enlever les # pour le but2 et le mainloop   
    
    
    
    
    
    
    
    
    
    
    