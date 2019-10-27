 /***************************************************************************
 * Copyright (C) 2004 by Bouard Eric *
 * eric@bouard.org *
 * wwww.bouard.org *
 * This program is free software; you can redistribute it and/or modify *
 * it under the terms of the GNU General Public License as published by *
 * the Free Software Foundation; either version 2 of the License, or *
 * (at your option) any later version. *
 * *
 * This program is distributed in the hope that it will be useful, *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the *
 * GNU General Public License for more details. *
 * *
 * You should have received a copy of the GNU General Public License *
 * along with this program; if not, write to the *
 * Free Software Foundation, Inc., *
 * 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA. *
 ***************************************************************************/
 include"String.h"

 using namespace std;


 int main(int argc, char *argv[])
 {
 char testchar;
 String test;

 String test1 = " Ceci est un Test ";
 String test2;

 test2 = test1;
 String test3 = test1.Minuscule();

 cout <<"Test de la classe String" << endl;
 cout <<"Test2 ="<< test2.val() << endl;
 cout <<"Test3 ="<< test3.val() << endl;
 test2 = test3.SansEspaceGauche();
 cout <<"test3.SansEspaceGauche()="<< test2.val() << endl;
 test2 = test3.Gauche(50);
 cout <<"test3.Gauche(50)="<< test2.val() << endl;

 test2 = test3.Gauche(4);
 cout <<"test3.Gauche(4)="<< test2.val() << endl;


 test2 = test3.Gauche();
 cout <<"test3.Gauche()="<< test2.val() << endl;

 test3 = " ";
 test2 = test3.SansEspaceDroite();
 cout <<"test3.SansEspaceDroite()="<< test2.val() << endl;

 test2 = test1.SansEspace();
 cout <<"test1.SansEspace()=" << test2.val() << endl;

 test2 = test2.Droite(4);
 cout <<"test2.Droite(4)=" << test2.val() << endl;

 test2 = test1.Milieu(3,4);
 cout <<"test1.Milieur(3,4)=" << test2.val() << endl;

 test2 = (String)"Ceci" + " est un Test";

 cout <<"(String)Ceci + est un Test=" << test2.val() << endl;

 test2 = (String)"ABC" + TAB + "" + TAB + "" + TAB + "DEF";
 test3 = test2.ExtraitChaine(1);
 cout <<"test3 = test2.ExtraitChaine(1)" << test3.val() << endl;
 test3 = test2.ExtraitChaine(2);
 test3 = test2.ExtraitChaine(4);
 test3 = test2.ExtraitChaine(5);
 test3 += "xxx";
 test3 += test3;
 if (test1 == " Ceci est un Test ")
 {
 cout <<"test d'égalité == " << endl;
 }

 if (test1 != " Ceci est un mauvais Test ")
 {
 cout <<"test d'inégalité != " << endl;
 }
 cout <<"test1 de << test1 =" << test1 << endl;
 testchar = test3[1];
 test3=test1.Repete("XY", 4);
 cout <<"test1.Repete('XY', 4) =" << test1.Repete("XY", 4) << endl;
 test3=test1.Complete(21,'X');
 cout <<"Terminé"<< endl;
 return EXIT_SUCCESS;
 }