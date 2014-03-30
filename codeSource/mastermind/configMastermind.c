//fichier : configMastermind.h


#include "configMastermind.h"

//*****************************************************************************************************************
//fonction : fonction qui g�re la fen�tre de configuration du mastermind
//parametres : l'�cran, pointeur sur le choix des couleurs, et le choix des manches
//retour : boolean sur l'�tat de la fen�tre
//*****************************************************************************************************************
int configMastermind(SDL_Surface *ecran, int *choixCouleurs, int *choixManches)
{
    int continuer = 1, curseur = 1, couleursBis = *choixCouleurs, manchesBis = *choixManches; //on stockes la valeur des pointeurs suite a des problemes
    //de modification des variables dans la boucle des �v�nements
    SDL_Surface *parametres = NULL, *boiteSelection1 = NULL, *Scurseur = NULL;
    SDL_Rect positionParametres, positionCurseur, positionSelection[2];
    SDL_Event event;

    int mettreEnSurbrillance=0;
    SDL_Surface *ocre=NULL;
    SDL_Rect posOcre;


    SDL_WM_SetCaption("Configuration", NULL); //titre de la fen�tre

    positionParametres.x = 0; //position de l'�cran de param�tres (pr�c�dent le jeu)
    positionParametres.y = 0;

    positionCurseur.x = 261; //curseur pour la s�lection des param�tres
    positionCurseur.y = 113;

    positionSelection[0].x = 449; //position de la s�lection courante (param�tres)
    positionSelection[0].y = 109;

    positionSelection[1].x = 454; // position de la boite de s�lection de valeurs (param�tres)
    positionSelection[1].y = 143;

    posOcre.x = CONFIGM_POS_BOUTON_VALIDER_X;
    posOcre.y = CONFIGM_POS_BOUTON_VALIDER_Y;

    parametres = IMG_Load("./images/parametresMastermind.png");// on charge le fond "param�tres"
    SDL_BlitSurface(parametres, NULL, ecran, &positionParametres);//on la colle sur l'�cran

    boiteSelection1 = SDL_LoadBMP("./images/boiteSelection1.bmp");//on charge la boite de selection

    SDL_SetColorKey(boiteSelection1, SDL_SRCCOLORKEY, SDL_MapRGB(boiteSelection1->format, 0, 162, 232));//on d�finit un canal alpha (pour la transparence)

    SDL_BlitSurface(boiteSelection1, NULL, ecran, &positionSelection[0]); //on colle les boites de selection par d�faut
    SDL_BlitSurface(boiteSelection1, NULL, ecran, &positionSelection[1]);

    Scurseur = SDL_LoadBMP("./images/curseur.bmp"); //on charge le curseur
    SDL_BlitSurface(Scurseur, NULL, ecran, &positionCurseur);//on colle
    SDL_SetColorKey(Scurseur, SDL_SRCCOLORKEY, SDL_MapRGB((Scurseur)->format, 92, 96, 96));

    SDL_Flip(ecran); //Raffraichissement

    //initialisation de la surbrillance du bouton valider
    ocre=SDL_CreateRGBSurface(SDL_HWSURFACE, 110, 47, 32, 0, 0, 0, 0);//on cree le rectangle a colorer en ocre(de 126x48 pixels)
    SDL_FillRect(ocre, NULL, SDL_MapRGB(ecran->format, COLOR_TRANSP_BOUTON_BON_R, COLOR_TRANSP_BOUTON_BON_V, COLOR_TRANSP_BOUTON_BON_B));//on colorie en  ocre
    SDL_SetAlpha(ocre, SDL_SRCALPHA, 128);//definition de sa transparence


    while(continuer) //premi�re boucle de gestion des �v�nements
    {
        SDL_WaitEvent(&event); /* R�cup�ration de l'�v�nement dans event */
        switch(event.type) /* Test du type d'�v�nement */
        {
        case SDL_QUIT: // Si c'est un �v�nement de type "Quitter" //
            SDL_Delay(20);
            //pas la peine de liberer puisque toute la memoire va etre desalouee
            return 0;
            break;
        case SDL_KEYDOWN: //si appui d'une touche
            SDL_Delay(20); //petit d�lai pour lib�rer le processeur

            switch (event.key.keysym.sym)
            {
                case SDLK_ESCAPE: //Appui sur la touche Echap, on revient � l'accueil
                    SDL_FreeSurface(ocre);
                    SDL_FreeSurface(Scurseur); //on lib�re les surfaces utilis�es pour les param�tres
                    SDL_FreeSurface(parametres);
                    SDL_FreeSurface(boiteSelection1);
                    return 1;
                    break;
                case SDLK_DOWN: //si touche "bas"
                    if(curseur < 2) // si on est a la premi�re position
                    {
                        positionCurseur.y += 31; //on baisse le curseur
                        curseur++; //on incr�mente curseur (indiquant sa position)
                    }
                    else //si on est a la deuxi�me position, on revient a la premi�re
                    {
                        positionCurseur.y -= 31;  //le curseur remonte
                        curseur --; //on d�cr�mente curseur (indiquant sa position)
                    }
                    break;
                case SDLK_UP: //si touche "haut"
                    if(curseur > 1) //meme raisonnement que la touche bas mais inverse
                    {
                        positionCurseur.y -= 31;
                        curseur--;
                    }
                    else
                    {
                        positionCurseur.y += 31;
                        curseur ++;
                    }
                    break;
                case SDLK_LEFT: //si touche "gauche"
                    if(curseur == 1) // si on est � la premi�re position, on modifie donc le choix du nombre de couleurs
                    {
                        if(couleursBis > 4) // si le choix est sup�rieur a 4, on baisse ce choix de 1
                        {
                            couleursBis--;
                            positionSelection[0].x -= 34; //on d�cale la boite a gauche pour mod�liser ce choix

                        }
                        else // si le choix est a 4, on passe a 8 (3 n'�tant pas possible)
                        {
                            couleursBis += 4;
                            positionSelection[0].x += 136; //on d�cale la boite

                        }
                    }
                    else if(curseur == 2) // si on est a la position 2, on modifie le nombre de manches
                    {
                        if(manchesBis > 2) // si le choix est sup�rieur a deux, on d�cr�mente
                        {
                            manchesBis--;
                            positionSelection[1].x -= 41; //on d�cale la boite

                        }
                        else //si on est deja a deux manches, on passe a quatre (2 manches minimum)
                        {
                            manchesBis += 2;
                            positionSelection[1].x += 82; //on d�cale la boite
                        }
                    }

                    break;
                case SDLK_RIGHT: //touche "droite", meme raisonnement que a gauche mais inverse
                    if(curseur == 1)
                    {
                        if(couleursBis < 8)
                        {
                            couleursBis++;
                            positionSelection[0].x += 34;

                        }
                        else
                        {
                            couleursBis -= 4;
                            positionSelection[0].x -= 136;

                        }
                    }
                    else if(curseur == 2)
                    {
                        if(manchesBis < 4)
                        {
                            manchesBis++;
                            positionSelection[1].x += 41;

                        }
                        else
                        {
                            manchesBis -= 2;
                            positionSelection[1].x -= 82;
                        }
                    }

                    break;
                default:
                    break;

            }
            break;
        case SDL_MOUSEBUTTONUP: // Clic de la souris
            SDL_Delay(20);
            if (event.button.button == SDL_BUTTON_LEFT) // si clic gauche
            {
                if (event.button.x > CONFIGM_POS_BOUTON_VALIDER_X && event.button.x < CONFIGM_POS_BOUTON_VALIDER_X+CONFIGM_TAILLE_BOUTON_VALIDER_X
                    && event.button.y < CONFIGM_POS_BOUTON_VALIDER_Y+CONFIGM_TAILLE_BOUTON_VALIDER_Y && event.button.y > CONFIGM_POS_BOUTON_VALIDER_Y) //si appui sur la zone "continuer"
                {
                    continuer = 0; // on sort de la boucle
                }
            }
            break;
        case SDL_MOUSEMOTION:
            if (event.button.x > CONFIGM_POS_BOUTON_VALIDER_X && event.button.x < CONFIGM_POS_BOUTON_VALIDER_X+CONFIGM_TAILLE_BOUTON_VALIDER_X
                && event.button.y < CONFIGM_POS_BOUTON_VALIDER_Y+CONFIGM_TAILLE_BOUTON_VALIDER_Y && event.button.y > CONFIGM_POS_BOUTON_VALIDER_Y){//souris sur le bouton valider
                mettreEnSurbrillance=1;//on est maintenant, ou toujours sur un bouton
                break;
            }
            else {mettreEnSurbrillance=0;}//si on est sur aucun des boutons

            break;
        default:
            break;
        }

        SDL_BlitSurface(parametres, NULL, ecran, &positionParametres); // on colle le fond

        SDL_BlitSurface(boiteSelection1, NULL, ecran, &positionSelection[0]); // la boite de s�lection a la premiere position

        SDL_BlitSurface(boiteSelection1, NULL, ecran, &positionSelection[1]); //la boite de s�lection a la deuxi�me position

        SDL_BlitSurface(Scurseur, NULL, ecran, &positionCurseur); // le curseur

        if (mettreEnSurbrillance==1){
            if (ocre!=NULL){
                SDL_BlitSurface(ocre, NULL, ecran, &posOcre);//on colle l ocre
            }else {fprintf(stderr, "ConfigMastermind : Erreur affichage, NULL Pointeur Exception : ocre\n");}
        }

        SDL_Flip(ecran); //Raffraichissement
    }

    *choixCouleurs = couleursBis;
    *choixManches = manchesBis;


    SDL_FreeSurface(ocre);
    SDL_FreeSurface(Scurseur); //on lib�re les surfaces utilis�es pour les param�tres
    SDL_FreeSurface(parametres);
    SDL_FreeSurface(boiteSelection1);

    return 2;
}


