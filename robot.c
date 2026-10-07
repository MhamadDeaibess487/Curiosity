#include "robot.h"
#include "terrain.h"

void init_robot(Robot *r, int x, int y, Orientation o){
    r->x=x;
    r->y=y;
    r->o=o;
}
void avancer(Robot *r){
    if(r->o==Est){
        r->x=(r->x)+1;
    }else if(r->o==Sud){
        r->y=(r->y)+1;
    }else if(r->o==Ouest){
        r->x=(r->x)-1;
    }else if (r->o==Nord){
        r->y=(r->y)-1;
    }
}

void tourner_a_gauche(Robot *r){
    if(r->o==Est){
        r->o=Nord;
    }else if(r->o==Sud){
        r->o=Est;
    }else if(r->o==Ouest){
        r->o=Sud;
    }else if (r->o==Nord){
        r->o=Ouest;    }
}

void tourner_a_droite(Robot *r){
    if(r->o==Est){
        r->o=Sud;
    }else if(r->o==Sud){
        r->o=Ouest;
    }else if(r->o==Ouest){
        r->o=Nord;
    }else if (r->o==Nord){
        r->o=Est; 
    }
}

void position(Robot *r, int *x, int *y){
    *x=r->x;
    *y=r->y;
}

int abscisse(Robot *r){
    return r->x;
}
int ordonnee(Robot *r){
    return r->y;
}

Orientation orient(Robot *r){
    return r->o;
}

void position_devant(Robot *r, int *x, int *y){
    if(r->o==Est){
        *x=(r->x)+1;
        *y=r->y;
    }else if(r->o==Sud){
        *y=(r->y)+1;
        *x=r->x;
    }else if(r->o==Ouest){
        *x=(r->x)-1;
        *y=r->y;
    }else if (r->o==Nord){
        *y=(r->y)-1;
        *x=r->x;
    }
    

}