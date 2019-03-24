# Ohjelma: Kertolaskupeli, calculator game

"""
Kuvaus
Ohjelma on siis yksinkertainen peli, jossa käyttäjä voi harjoittaa kertolaskutaitojaan / kokeilla ihan huviksi, miten ne sujuvat.
Haastetta voi lisätä säätämällä ylärajaa laskuille 2-15 väliltä. Haastetasoa voi myös muuttaa asteikolla 1-3, jolloin kertolaskuja monimutkaistetaan
asettamalla lisää peräkkäisiä kertolaskuja.
Ohjelma tallentaa myös peleistä pistetietoja. Yritysten määrää / peli, voi myös muuttaa asetuksista
Ohjelma on perusteiltaan yksinkertainen graafinen käyttöliittymä
"""
from tkinter import *
from random import randint
class Kertolaskupeli:
    def __init__(self):
        """
        Konstruktori koko luokalle
        """
        # Luodaan Tkinter ikkuna ja ladataan konfiguraatiot
        self.__ikkuna = Tk()
        self.configures()
        # Alustetaan koko pelin kannalta oleelliset tietorakenteet / muuttujat
        self.__score = 0
        self.__scoreboard = {}
        self.__scoremultiplier = 1
        self.__nick = ""
        self.__low = 0
        self.__high = 10
        self.__turn = 0
        self.__wrongcount = 1 # montako saa olla väärin
        self.__labelcount = "off" # onko olemassa "Väärin" label
        self.__complexity = 1
        self.__nickrestrict = 10
        # Alkusanat
        self.__welcome = Label(self.__ikkuna,text="Tervetuloa kertolaskupeliin!",height=3)
        self.__welcome.pack()
        self.__welcome.config(font=("Ubuntu",18))
        self.__text = Label(self.__ikkuna,text="Tehtävänäsi on laskea julmia kertolaskuja, testaa kuinka selviät! \n"
                                               "Jokaisesta oikeasta vastauksesta saat yhden pisteen \n"
                                               "Voit säätää peliin liittyviä asetuksia valikon kautta \n",font=1)
        self.__text.pack()
        self.__nicklabel = Label(self.__ikkuna, text="Pelaajanimesi (max 10 merkkiä)",font=15)
        self.__nicklabel.pack()
        self.__nickentry = Entry(self.__ikkuna,font=15)
        self.__nickentry.pack(pady=10)
        # Asetetaan entry-ikkuna toimimaan niin, että  siihen voi suoraan kirjoittaa ilman erillistä klikkaamista
        self.__nickentry.focus()
        self.__aloita = Button(self.__ikkuna,text="Aloita peli",command=self.namecheck,height=2,width=12)
        self.__aloita.pack()
        self.__ikkuna.mainloop()
    def configures(self):
        """
        Lataa ikkunaan liittyviä asetuksia ja navmenun
        :return:
        """
        self.__ikkuna.title("| Some Calculator Game |")
        self.__ikkuna.geometry("600x600")
        # Luodaan navigointimenu
        menubar = Menu(self.__ikkuna)
        filemenu = Menu(menubar, tearoff=0,font=5)
        filemenu.add_command(label="Ohjelman alustus",command=self.clear)
        filemenu.add_command(label="Asetukset",command=self.conf)
        filemenu.add_command(label="Scoreboard",command=self.scoreboard)
        filemenu.add_separator()
        filemenu.add_command(label="Lopeta ohjelma",command=self.destroy)
        menubar.add_cascade(label="Pelin konfigurointi", menu=filemenu)
        self.__ikkuna.config(menu=menubar)
    def scoreboard(self):
        """
        Tulostaulu, johon tulostetaan pelien tuloksia
        :return:
        """
        # Asetetaan uusi ikkuna
        scoreboard = Toplevel(self.__ikkuna)
        scoreboard.geometry("600x600")
        scoreboard.title("| Scoreboard |")
        # Tulostetaan tuloksia peleistä, jos niitä on
        if (len(self.__scoreboard) != 0):
            Label(scoreboard,text="Pelien tuloksia alhaalla \n",font=20).pack()
            for score in self.__scoreboard:
                Label(scoreboard,font=12,text=" | "+str(score)+" | "+str(self.__scoreboard[score])+" | ").pack()
        else:
            Label(scoreboard,text="Tuloksia peleistä ei ole vielä",font=20).pack()
    def conf(self):
        """
        Asetusten muutos -ikkunaan liittyvät ominaisuudet ja konfiguroinnit
        :return:
        """
        self.__configure = Toplevel(self.__ikkuna)
        configure = self.__configure
        configure.geometry("600x600")
        configure.title("| Asetusten muutos |")
        # Asetusten muutokseen liittyvät tekstit ja toiminnot alla
        info = Label(configure,text="Alla on peliin / ohjelmaan liittyviä asetuksia, joita voit muuttaa \n",font=20)
        info.pack()
        # jos nickname on asetettu
        if (self.__nick != ""):
            nick = Label(configure,text="Pelaat tällä hetkellä nimellä: "+str(self.__nick)+"\n",font=15)
            nick.pack()
            nickchange = Label(configure,text="Vaihda nimeä kirjoittamalla uusi pelinimi: ")
            nickchange.pack()
            self.__rename = Entry(configure)
            self.__rename.pack()
            nickbutton = Button(configure,text="Vaihda pelinimi, max. 10 merkkiä",command=self.rename)
            nickbutton.pack()
        mult_label = Label(configure,text="\n Säädä yritysten määrää / peli, tällä hetkellä: "+str(self.__wrongcount),font=15)
        mult_label.pack()
        # Luodaan skaalautuva valikko pistekerrointa varten
        self.__var_score = IntVar()
        scale = Scale(configure, from_=1, to=10, orient=HORIZONTAL,variable=self.__var_score,activebackground="green")
        scale.pack()
        button = Button(configure, text="Säädä", command=self.trying)
        button.pack()
        self.__label = Label(configure)
        self.__label.pack()
        multiply_setting = Label(configure,
                                 text="\n Säädä ylärajaa kertotauluille. Nykyinen: "+str(self.__high),font=15)
        multiply_setting.pack()
        # Luodaan samanlainen valikko nyt kertotaulujen ylärajaakin varten
        self.__var = IntVar()
        scale = Scale(configure, from_=2, to=15,orient=HORIZONTAL, variable=self.__var,activebackground="red")
        scale.pack()
        button = Button(configure, text="Säädä",command=self.set_high)
        button.pack()
        self.__label = Label(configure)
        self.__label.pack()
        complexity_setting = Label(configure,text="\n Säädä vaikeustasoa lisäämällä kerrottavien määrää. Nykyinen: "+str(self.__complexity),font=15)
        complexity_setting.pack()
        # Luodaan vielä yksi samanlainen valikko vaikeustasoa varten
        self.__compvar = IntVar()
        comp_scale = Scale(configure, from_=1, to=3, orient=HORIZONTAL,
                           variable=self.__compvar, activebackground="yellow")
        comp_scale.pack()
        comp_button = Button(configure,text="Säädä",command=self.set_complex)
        comp_button.pack()
        self.__complabel = Label(configure)
        self.__complabel.pack()
        refresh = Button(configure,text="Päivitä",command=self.conf_ref)
        refresh.pack(side=BOTTOM)
    # Tästä eteenpäin ovat metodit, jotka liittyvät pelin asetuksiin
    # Metodit lisäävät siis toimintoja "Asetukset" välilehdelle
    def rename(self):
        """
        Yksinkertaisesti muuttaa halutun nimen, kun pelinimi on jo kerran asetettu
        :return:
        """
        name = self.__rename.get()
        if (len(name) != 0 and len(name) <= self.__nickrestrict):
            self.__nick = name
            self.__namelabel.forget()
            # Lisätään vähän tsemppausta
            self.__namelabel = Label(self.__ikkuna,
                                     text="Tsemppiä " + str(self.__nick))
            self.__namelabel.pack(side=TOP)
        else:
            pass
    def set_complex(self):
        """
        Muuttaa vaikeustasoa
        :return:
        """
        complexity = self.__compvar.get()
        self.__complexity = complexity
    def set_high(self):
        """
        Muutta yläraja-arvoa kertolaskuille
        :return:
        """
        high = self.__var.get()
        self.__high = high
    def conf_ref(self):
        """
        Uusien konfiguroinnien lataaminen
        :return:
        """
        self.__configure.destroy()
        self.conf()
    def trying(self):
        """
        Pistekertoimen muunnin
        :return:
        """
        trying = self.__var_score.get()
        self.__wrongcount = trying
    # Tähän loppuvat "Asetukset" välilehden metodit
    # Alempana ikkunan alustus ja tyhjennys metodit
    def clear(self):
        """
        Ikkunan alustus
        Siltä varalta, jos jokin menee pelissä / ohjelmassa vikaan tai halutaan aloittaa alusta ylipäätää
        :return:
        """
        self.__ikkuna.destroy()
        self.__init__()
    def destroy(self):
        """
        Ohjelman lopetus
        :return:
        """
        self.__ikkuna.destroy()
    # Tsekataas toi nimi ennen pelin aloitusta
    def namecheck(self):
        """
        Tarkistaa, että nimi on täytetty edes jossakin muodossa
        :return:
        """
        name = self.__nickentry.get()
        if (len(name) != 0 and len(name) <= self.__nickrestrict):
            self.__nicklabel.forget()
            self.__nickentry.forget()
            self.__nick = name
            self.__namelabel = Label(self.__ikkuna,text="Tsemppiä "+str(self.__nick),font=15,fg="green")
            self.__namelabel.pack(side=TOP)
            self.kertolasku()
        else:
            pass
    # Varsinaisen peliohjelman toimintamäärittelyt alkavat alapuolella
    # Kertolaskuun liittyvät metodit alkavat
    def kertolasku(self,event=None):
        """
        Aloittaa kertolaskupelin alustan
        :return:
        """
        self.__aloita.forget()
        self.__welcome.forget()
        self.__text.forget()
        if (self.__labelcount == "on"):
            self.__error.forget()
        self.__gameframe = Frame(self.__ikkuna)
        self.__gameframe.pack(side=TOP)
        # Määritellään luvut, joita pelissä kerrotaan
        self.__yksi = randint(self.__low, self.__high)
        self.__kaksi = randint(self.__low, self.__high)
        self.__kolme = randint(self.__low,self.__high)
        self.__neljä = randint(self.__low,self.__high)
        # Määritetään vaikeustason perusteella
        if (self.__complexity == 1):
            self.__result = self.__yksi * self.__kaksi
            self.__label = Label(self.__gameframe,
                                 text=str(self.__yksi) + " * " + str(self.__kaksi),font=25,height=3)
            self.__label.pack()
        elif (self.__complexity == 2):
            self.__result = self.__yksi*self.__kaksi*self.__kolme
            self.__label = Label(self.__gameframe,text=str(self.__yksi)+" * "+str(self.__kaksi)+" * "+str(self.__kolme),font=25,height=3)
            self.__label.pack()
        else:
            self.__result = self.__yksi * self.__kaksi * self.__kolme * self.__neljä
            self.__label = Label(self.__gameframe,
                                 text=str(self.__yksi) + " * " + str(
                                     self.__kaksi) + " * " + str(self.__kolme)+" * "+str(self.__neljä),
                                 font=25, height=3)
            self.__label.pack()
        self.__entryresult = Entry(self.__gameframe,font=25)
        self.__entryresult.pack(pady=10)
        # Asetetaan entry-widget toimimaan suoraan enteriä painamalla ja lisätään keskitys, joten widgettiin voi suoraan kirjoittaa tekstiä
        self.__entryresult.focus()
        self.__entryresult.bind('<Return>',self.tarkista)
        self.__check = Button(self.__gameframe, text="Tarkista",command=self.tarkista)
        self.__check.pack(side=LEFT)
        self.__answer = Button(self.__gameframe,text="En tiedä / Uusi peli",command=self.wrong)
        self.__answer.pack(side=RIGHT)
    def tarkista(self,event=None):
        """
        Tarkistaa tuloksen oikeellisuuden
        :return:
        """
        try:
            tulos = int(self.__entryresult.get())
            if (self.__result == tulos):
                self.__oikein = Label(self.__gameframe, text="Oikein")
                self.__oikein.pack()
                self.__score += self.__scoremultiplier
                self.__gameframe.forget()
                self.kertolasku()
            else:
                # Tarkistetaan, montako yritystä yhdessä pelissä voi olla
                if (self.__turn < self.__wrongcount):
                    self.__turn += 1
                    if (self.__labelcount == "on"):
                        self.__error.forget()
                        self.__error = Label(self.__ikkuna,text="Vastaus oli väärin, yritä uudelleen")
                        self.__error.pack(pady=12)
                    else:
                        self.__labelcount = "on"
                        self.__error = Label(self.__ikkuna,text="Vastaus oli väärin, yritä uudelleen")
                        self.__error.pack(pady=12)
                else:
                    self.wrong()
        except ValueError:
            # Ei tehdä mitään, jos yritetään syöttää jotakin muuta kuin pitäisi
            pass
    def wrong(self):
        """
        Kun tulos on väärä käsitellään kyseinen tieto ja lisätään pistetiedot samalla
        :return:
        """
        self.__check.forget()
        self.__answer.forget()
        self.__entryresult.destroy()
        if (self.__labelcount == "on"):
            self.__error.forget()
        self.__wrongframe = Frame(self.__gameframe)
        self.__wrongframe.pack()
        self.__wrong = Label(self.__wrongframe,
                             text="Oikea vastaus olisi ollut " + str(
                                 self.__result))
        self.__wrong.pack()
        self.__scores = Label(self.__wrongframe,text="\n Sait "+str(self.__score)+"p")
        self.__scores.pack()
        # Lisätään vähän kannustushuutoja
        if (self.__scoremultiplier == 1):
            if (self.__score >= 25):
                textvar = "Erinomainen tulos!"
            elif (self.__score >= 10 and self.__score < 25 and self.__scoremultiplier==1):
                textvar = "Hyvä tulos!"
            elif (5<=self.__score < 10):
                textvar = "Lisää treeniä vaan!"
            elif (self.__score < 5):
                textvar = "Noh, harjoittelu tekee mestarin!"
            self.__good_label = Label(self.__wrongframe, text=textvar)
            self.__good_label.pack()
        # Lisätään ehtoja sille, milloin pisteitä lisätään scoreboardiin
        # Tulos lisätään vain jos sitä ei jo ole scoreboardissa ja tulos > 0
        if (self.__nick in self.__scoreboard and self.__score not in self.__scoreboard[self.__nick]):
            if (self.__score > 0):
                self.__scoreboard[self.__nick] += [self.__score]
        else:
            if (self.__score > 0):
                self.__scoreboard[self.__nick] = [self.__score]
        self.__somebutton = Button(self.__wrongframe, text="Aloita uusi peli",
                                   command=self.refresh)
        self.__somebutton.pack()
    def refresh(self):
        """
        Alustaa pelialustan ja poistaa vanhat widgetit tieltä
        :return:
        """
        self.__wrongframe.forget()
        self.__gameframe.forget()
        self.__score = 0
        self.__turn = 0
        self.__labelcount = "off"
        self.kertolasku()
def main():
    Peli = Kertolaskupeli()
main()
