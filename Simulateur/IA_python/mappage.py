from tkinter import *
from math import *
from time import *
from random import *
from generation import *



affiche_murs(murs);

map_murs = [];
pos_l = None;
pos_c = None;
vect_l_b = 0; #vecteur ligne étape d'avant
vect_c_b = 1; #vecteur colonne étape d'avant

##########################################################################################################################################################################


#initialise la matrice à mapper
def init_map():
    global cases, map_murs, pos_c, pos_l;
    pos_l=0;
    pos_c=0;
    for j in range(cases):
        li=[];
        for i in range(cases):
            struct=[0,0,0,0,j*cases+i];
            li.append(struct);
        map_murs.append(li);



#test s'il y a un mur en direction du vecteur
#return 1 si trou
def test_mur(pos_l, pos_c, v_ligne, vect_col):
    if(murs[pos_l][pos_c][abs(vect_col)*(vect_col+2)+abs(v_ligne)*(v_ligne+1)]==0):
        return 1;
    return 0;
    

#test si le robot est sur une des 4 cases de l'arrivée,
#pos_l indice de la position en ligne
#return 1 si gagné, 0 sinon
def test_gagne():
    global pos_l, pos_c;
    vect= [-1, 1];
    for i in vect:
        if(test_mur(pos_l, pos_c, 0, i)):
            if(test_mur(pos_l, pos_c+i, -1*i, 0)):
                if(test_mur(pos_l+i, pos_c+i, 0, -1*i)):
                    if(test_mur(pos_l+i, pos_c, i, 0)):
                        print('gagné1!', i, pos_l, pos_c)
                        return 1;
                        
    for k in vect:
        if(test_mur(pos_l, pos_c, k, 0)):
            if(test_mur(pos_l-k, pos_c, 0, k)):
                if(test_mur(pos_l-k, pos_c+k, -1*k, 0)):
                    if(test_mur(pos_l, pos_c+k, 0, -1*k)):
                        print('gagné2!', k, pos_l, pos_c)
                        return 1;
        
            
    return 0;
    
    
#Test avec les capteurs s'il y a un ou plusieurs murs à proximité du robot
#capteur1 = capteur gauche
#capteur2 = capteur avant
#capteur3 = capteur droit
def check_capteur(vect_l, vect_c):
    global murs, pos_l, pos_c;
    
    print('check : ', vect_l, vect_c, pos_l, pos_c);
    if(vect_l==0):
        capteur1 = murs[pos_l][pos_c][1+vect_c];
        capteur2 = murs[pos_l][pos_c][2+vect_c];
        capteur3 = murs[pos_l][pos_c][1-vect_c];
        
    
    if(vect_c==0):
        capteur1 = murs[pos_l][pos_c][2-vect_l];
        capteur2 = murs[pos_l][pos_c][1-vect_l];
        capteur3 = murs[pos_l][pos_c][2+vect_l];
        
        
    print(capteur1, capteur2, capteur3);
    return [capteur1, capteur2, capteur3];
    
#Mise à jour de la case "actuelle" de la matrice en fonction des capteurs
def maj_mapping(vect_l, vect_c, capteur):
    global map_murs, pos_c, pos_l;
    if(vect_l==0):
        map_murs[pos_l][pos_c][1+vect_c] = capteur[0];
        map_murs[pos_l][pos_c][2+vect_c] = capteur[1];
        map_murs[pos_l][pos_c][1-vect_c] = capteur[2];
        return 1; 
    
    if(vect_c==0):
        map_murs[pos_l][pos_c][2-vect_l] = capteur[0];
        map_murs[pos_l][pos_c][1+vect_l] = capteur[1];
        map_murs[pos_l][pos_c][2+vect_l] = capteur[2];
        return 1;
    
    else:
        return 0;
    
  
#random pour obtenir un vecteur qui servira au déplacement du robot  
def rand_move():
    vect_rand = randint(1,21);
    vect_l = vect_rand%2*randrange(-1,2,2);
    vect_c = (vect_rand+1)%2*randrange(-1,2,2);
    return [vect_l, vect_c];
    
    
#Le robot se déplace aléatoirement à la case suivante s'il n'y a pas de mur
def move_map():
    global map_murs, pos_c, pos_l, vect_l_b, vect_c_b;
    n=1;
    vect_l_liste = [vect_c_b, vect_l_b, -1*vect_c_b, -1*vect_l_b];
    vect_c_liste = [-1*vect_l_b, vect_c_b, vect_l_b, -1*vect_c_b];
    print("Liste ligne : ", vect_l_liste);
    print("Liste colonne : ", vect_c_liste);
    
    vect_l = vect_l_liste[0];
    vect_c = vect_c_liste[0];
    print("vectl: ",vect_l,"     /////     vect_c : ", vect_c);
    print("mapmurs: ",map_murs[pos_l][pos_c][(1-vect_l)*abs(vect_l) + (2+vect_c)*abs(vect_c)]);
    print("capteur avant : ", check_capteur(vect_l, vect_c)[1]);
    while(map_murs[pos_l][pos_c][(1-vect_l)*abs(vect_l) + (2+vect_c)*abs(vect_c)]!=0 or check_capteur(vect_l, vect_c)[1]!=0 or pos_l+vect_l<0 or pos_l+vect_l>cases-1 or pos_c+vect_c<0 or pos_c+vect_c>cases-1):
        vect_l = vect_l_liste[n];
        vect_c = vect_c_liste[n];
        print("bloc");
        print("vectl: ",vect_l,"     /////     vect_c : ", vect_c);
        print("mapmurs: ",map_murs[pos_l][pos_c][(1-vect_l)*abs(vect_l) + (2+vect_c)*abs(vect_c)]);
        print("capteur avant : ", check_capteur(vect_l, vect_c)[1]);
        n=n+1;
    print('final : ', vect_l,"       vect_c : ", vect_c);
    return [vect_l, vect_c];
    
    
def main_init(): 
    global cases, map_murs, pos_c, pos_l; 
    init_map();
    capteur = check_capteur(0, 1);
    if(maj_mapping(0,1, capteur)!=1):
        print('Erreur maj_map');
        
    capteur = check_capteur(1, 0);
    if(maj_mapping(1,0, capteur)!=1):
        print('Erreur maj_map');
        
        
def maj_graph_map():
    global pos_c, pos_l, largeur_case;
    largeur_robot = largeur_case-10;
    can.create_rectangle(
        marge+largeur_case*pos_c+10,
        marge+largeur_case*pos_l+10,
        marge+largeur_case*(pos_c+1)-10,
        marge+largeur_case*(pos_l+1)-10,
        fill='#666555888');
    
def step():
    global pos_l, pos_c, map_murs, vect_l_b, vect_c_b;
    if (test_gagne()==1):
        print('fin...');
        return 1;
    else:
        print('pos_l : ', pos_l, 'pos_c : ', pos_c);
        vect_rand = move_map();
        vect_l = vect_rand[0]
        vect_c = vect_rand[1];
        vect_l_b = vect_l;
        vect_c_b = vect_c;
        capteur = check_capteur(vect_l, vect_c);
        maj_mapping(vect_l, vect_c, capteur);
        pos_l = pos_l + vect_l;
        pos_c = pos_c + vect_c;
        print('new pos : ', pos_l, pos_c);
        affiche_murs(map_murs); 
    maj_graph_map()
    return 0
    
###########################################################################################################################################################################☺

   


main_init()

but2=Button(fen, text="Next", command=step);
but2.grid(row=1, column=0);


fen.mainloop();








 





