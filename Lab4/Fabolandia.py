import threading
import random as ran
from datetime import datetime
import time

#Algunas variables Globales utilizadas
start_rc_q = 1
start_hh_q = 1
start_ps_q = 1
start_sr_q = 1

# Los strings para cada juego
RC = "Rollercoaster"
HH = "Horror House"
PS = "Pirate Ship"
SR = "Shooting Range"

# Semaphores
# Para los archivos de texto.
common_zone_log_sem = threading.Semaphore(1)
rc_log_sem = threading.Semaphore(1) 
hh_log_sem = threading.Semaphore(1) 
ps_log_sem = threading.Semaphore(1) 
sr_log_sem = threading.Semaphore(1) 
exit_log_sem = threading.Semaphore(1)

# Para la montaña rusa
q1 = threading.Semaphore(1)
rc_q_sem = threading.Semaphore(0)
rc_game_sem = threading.Semaphore(1)

# Para la casa del terror
q2 = threading.Semaphore(1)
hh_q_sem = threading.Semaphore(0)
hh_game_sem = threading.Semaphore(1)

# Para el barco pirata
q3 = threading.Semaphore(1)
ps_q_sem = threading.Semaphore(0)
ps_game_sem = threading.Semaphore(1)

# Para el tiro al blanco
q4 = threading.Semaphore(1)
sr_q_sem = threading.Semaphore(0)
sr_game_sem = threading.Semaphore(1)

"""
class Customer
Es la clase para cada cliente, recibe el nombre y el juego al que se subirá
Ademas contiene las siguientes funciones:
def log_entry: Escribe en el archivo zona comun, la persona, el tiempo de ingreso al parque, el juego al que ira, y el tiempo de la salida de la fila.
def log_game: Escribe en el archivo del juego ingresado, la persona, el tiempo que estuvo en la fila, y el tiempo que dejo la fila
def log_exit: Escribe en el archivo de salida.txt, la persona y el tiempo de salida del parque.
"""

class Customer:
    def __init__(self,name, game):
        self.name = name
        self.game = game
        self.entry_time = 0
        self.exit_time = 0

    def log_entry(self, filename,common_zone_log_sem):
        common_zone_log_sem.acquire()

        filezc = open(filename, 'a+')
        # Persona, IngresoParque,Juego,Salidafila
        filezc.write(
            str(self.name) + ", " + str(self.entry_time) + ", " + str(
                self.game) + ", " + str(self.exit_time) + "\n")
        filezc.close()
        common_zone_log_sem.release()

    def log_game(self, filename, game_log_sem ):
        game_log_sem.acquire()

        file_game = open(filename, 'a+')
        # Persona, tiempo en la fila, tiempo subir atraccion
        file_game.write(str(self.name) + ', ' + str(self.start_time) + ', ' + str(
                        self.exit_time) + '\n')
        file_game.close()
        game_log_sem.release()
    
    def log_exit(self, filename, exit_log_sem):
        exit_log_sem.acquire()

        file_game = open(filename, 'a+')
        # Persona, hora de salida del parque
        file_game.write(str(self.name) + ', ' + str(self.start_time) + '\n')
        file_game.close()
        exit_log_sem.release()


"""
class Rollercoaster
Es la clase para el juego de la Montaña rusa, recibe capacidad de la fila, duracion del juego y la capacidad del juego.
Ademas contiene las siguientes funciones:
def start_rc_thread: Crea el Thread para la montaña rusa.
def run_rc: Corre la montaña rusa. 
"""

class Rollercoaster:
    attendees = []

    def __init__(self, q_cap, dur, game_cap):
        self.game_capacitiy = game_cap
        self.queue_capacitiy = q_cap
        self.duration = dur

    def start_rc_thread(self):
        t_rc = threading.Thread(target = self.run_rc)
        t_rc.start()

    def run_rc(self):
        # print("In the Rollercoaster")
        while True:
            if len(self.attendees) >= self.game_capacitiy:
                # print("Rollercoaster Capacity met, preparing to start...")
                rc_game_sem.acquire()
                start_time = datetime.now().time()
                
                # game is running
                # print("Rollercoaster is running...")
                time.sleep(self.duration)

                for i in range(0,self.game_capacitiy):

                    self.attendees[0].exit_time = start_time
                    self.attendees[0].log_game('MontañaRusa.txt', rc_log_sem)

                    self.attendees[0].start_time = datetime.now().time()
                    self.attendees[0].log_exit('Salida.txt', exit_log_sem)
                    del self.attendees[0]

                # print(len(self.attendees))
                rc_game_sem.release()


"""
class HorrorHouse
Es la clase para el juego de la Casa del Terror, recibe capacidad de la fila, duracion del juego y la capacidad del juego.
Ademas contiene las siguientes funciones:
def start_hh_thread: Crea el Thread para la Casa del Terror.
def run_hh: Corre la Casa del Terror.
"""

class Horrorhouse:
    attendees = []

    def __init__(self, q_cap, dur, game_cap):
        self.game_capacitiy = game_cap
        self.queue_capacitiy = q_cap
        self.duration = dur

    def start_hh_thread(self):
        t_hh = threading.Thread(target=self.run_hh)
        t_hh.start()

    def run_hh(self):
        # print("In the Horror House")
        while True:
            if len(self.attendees) >= self.game_capacitiy:
                # print("Horror House Capacity met, preparing to start...")
                hh_game_sem.acquire()
                start_time = datetime.now().time()

                # game is running
                # print("Horror House is running...")
                time.sleep(self.duration)

                for i in range(0, self.game_capacitiy):

                    self.attendees[0].exit_time = start_time
                    self.attendees[0].log_game('CasaTerror.txt', hh_log_sem)

                    self.attendees[0].start_time = datetime.now().time()
                    self.attendees[0].log_exit('Salida.txt', exit_log_sem)

                    del self.attendees[0]

                # print(len(self.attendees))
                hh_game_sem.release()


"""
class Pirateship
Es la clase para el juego del Barco Pirata, recibe capacidad de la fila, duracion del juego y la capacidad del juego.
Ademas contiene las siguientes funciones:
def start_ps_thread: Crea el Thread para el Barco Pirata.
def run_ps: Corre el Barco Pirata.
"""

class Pirateship:
    attendees = []

    def __init__(self, q_cap, dur, game_cap):
        self.game_capacitiy = game_cap
        self.queue_capacitiy = q_cap
        self.duration = dur

    def start_ps_thread(self):
        t_ps = threading.Thread(target=self.run_ps)
        t_ps.start()

    def run_ps(self):
        # print("In the Pirate's of Caribbean")
        while True:
            if len(self.attendees) >= self.game_capacitiy:
                # print("Pirate's of Caribbean Capacity met, preparing to start...")
                ps_game_sem.acquire()
                start_time = datetime.now().time()

                # game is running
                # print("Pirate's of Caribbean is running...")
                time.sleep(self.duration)

                for i in range(0, self.game_capacitiy):

                    self.attendees[0].exit_time = start_time
                    self.attendees[0].log_game('BarcoPirata.txt', ps_log_sem)

                    self.attendees[0].start_time = datetime.now().time()
                    self.attendees[0].log_exit('Salida.txt', exit_log_sem)

                    del self.attendees[0]
                # print(len(self.attendees))
                ps_game_sem.release()


"""
class Shootingrange
Es la clase para el juego de Tiro al Blanco, recibe capacidad de la fila, duracion del juego y la capacidad del juego.
Ademas contiene las siguientes funciones:
def start_sr_thread: Crea el Thread para Tiro al Blanco.
def run_sr: Corre el Tiro al Blanco.
"""

class Shootingrange:
    attendees = []

    def __init__(self, q_cap, dur, game_cap):
        self.game_capacitiy = game_cap
        self.queue_capacitiy = q_cap
        self.duration = dur

    def start_sr_thread(self):
        t_sr = threading.Thread(target=self.run_sr)
        t_sr.start()

    def run_sr(self):
        # print("In Shooting Range")
        while True:
            if len(self.attendees) >= self.game_capacitiy:
                # print("Shooting Range Capacity met, preparing to start...")
                sr_game_sem.acquire()
                start_time = datetime.now().time()

                # game is running
                # print("Shooting Range is running...")
                time.sleep(self.duration)

                for i in range(0, self.game_capacitiy):

                    self.attendees[0].exit_time = start_time
                    self.attendees[0].log_game('TiroBlanco.txt', sr_log_sem)

                    self.attendees[0].start_time = datetime.now().time()
                    self.attendees[0].log_exit('Salida.txt', exit_log_sem)

                    del self.attendees[0]
                # print(len(self.attendees))
                sr_game_sem.release()


"""
class CommonZone
Es la clase para la zona común.
Ademas contiene las funciones:
def start_common_zone_thread: para empezar las colas de cada uno de los juegos.
def queue_people: Conteo de las veces que sale un juego, ademas de meter a las personas a la fila de espera antes del juego..
def send_to_game_queue: Manda a las personas a la queue del juego correspondiente.
"""

class CommonZone:
    rollercoasterQ = []
    horror_houseQ = []
    pirate_shipQ = []
    shooting_rangeQ = []

    def __init__(self):
        self.rc = Rollercoaster(10,5,10)
        self.rc.start_rc_thread()
        self.hh = Horrorhouse(8,3,2)
        self.hh.start_hh_thread()
        self.ps = Pirateship(15, 7, 5)
        self.ps.start_ps_thread()
        self.sr = Shootingrange(5, 2, 1)
        self.sr.start_sr_thread()

    def start_common_zone_thread(self):
        t_rc = threading.Thread(target = self.send_to_rc_queue)
        t_hh = threading.Thread(target = self.send_to_hh_queue)
        t_ps = threading.Thread(target = self.send_to_ps_queue)
        t_sr = threading.Thread(target = self.send_to_sr_queue)
        t_rc.start()
        t_hh.start()
        t_ps.start()
        t_sr.start()

    def queue_people(self, customer: Customer):
        # print(customer.name + " arrived to the common zone, logging entry...")
        customer.entry_time = datetime.now().time() # time object
        
        if customer.game == RC:
            self.rollercoasterQ.append(customer)
            global start_rc_q
            if start_rc_q:
                rc_q_sem.release()
                start_rc_q = 0

        elif customer.game == HH:
            self.horror_houseQ.append(customer)
            global start_hh_q
            if start_hh_q:
                hh_q_sem.release()
                start_hh_q = 0

        elif customer.game == PS:
            self.pirate_shipQ.append(customer)
            global start_ps_q
            if start_ps_q:
                ps_q_sem.release()
                start_ps_q = 0

        elif customer.game == SR:
            self.shooting_rangeQ.append(customer)
            global start_sr_q
            if start_sr_q:
                sr_q_sem.release()
                start_sr_q = 0
        else:
            print(" Why are you even here dude? D:")

    # Solo para printear, no se utiliza para nada mas. DESCOMENTAR los self.status para probar.
    def status(self):
        print("Status of Games:")
        print("Rollercoaster: ", len(self.rollercoasterQ), " attendees.")
        print("Horror House: ", len(self.horror_houseQ), " attendees.")
        print("Pirate Ship: ", len(self.pirate_shipQ), " attendees.")
        print("Shooting Range: ", len(self.shooting_rangeQ), " attendees.")
        time.sleep(2)

    def send_to_rc_queue(self ):

        while True:
            # print("IF THIS CHANGES THE RC IS WORKING: ",len(self.rc.attendees))
            if len(self.rollercoasterQ) == 0:
                # self.status()
                global start_rc_q
                # print("Empty Queue")
                start_rc_q = 1
                rc_q_sem.acquire()

            if len(self.rollercoasterQ) > 0:

                # print("Non Empty Queue")
                q1.acquire()
                # print("In Q for RCQ: ",len(self.rollercoasterQ))
                # print("In Q for RC: ",len(self.rc.attendees))
                # print("Current Q in RC: ",self.rc.queue_capacitiy)
                if len(self.rc.attendees) == self.rc.queue_capacitiy:
                    # print("Q is full")
                    q1.release()

                else:
                    # print("Adding to RC Q.")
                    self.rollercoasterQ[0].exit_time = datetime.now().time()

                    #loggear
                    self.rollercoasterQ[0].log_entry('ZonaComun.txt', common_zone_log_sem)

                    self.rollercoasterQ[0].start_time = datetime.now().time()
                    self.rc.attendees.append(self.rollercoasterQ[0])
                    del self.rollercoasterQ[0]
                    q1.release()
                    time.sleep(1)

    def send_to_hh_queue(self):

        while True:
            # print("IF THIS CHANGES THE HH IS WORKING: ", len(self.hh.attendees))
            if len(self.horror_houseQ) == 0:
                # self.status()
                global start_hh_q
                # print("Empty Queue")
                start_hh_q = 1
                hh_q_sem.acquire()

            if len(self.horror_houseQ) > 0:
                # self.status()
                # print("Non Empty Queue")
                q2.acquire()
                # print("In Q for HHQ: ", len(self.horror_houseQ))
                # print("In Q for HH: ", len(self.hh.attendees))
                # print("Current Q in HH: ", self.hh.queue_capacitiy)
                if len(self.hh.attendees) == self.hh.queue_capacitiy:
                    # print("Q is full")
                    q2.release()
                else:
                    # print("Adding to HH Q.")
                    self.horror_houseQ[0].exit_time = datetime.now().time()

                    # loggear
                    self.horror_houseQ[0].log_entry('ZonaComun.txt', common_zone_log_sem)

                    self.horror_houseQ[0].start_time = datetime.now().time()
                    self.hh.attendees.append(self.horror_houseQ[0])
                    del self.horror_houseQ[0]
                    q2.release()
                    time.sleep(1)

    def send_to_ps_queue(self):

        while True:
            # print("IF THIS CHANGES THE PS IS WORKING: ", len(self.ps.attendees))
            if len(self.pirate_shipQ) == 0:
                # self.status()
                global start_ps_q
                # print("Empty Queue")
                start_ps_q = 1
                ps_q_sem.acquire()

            if len(self.pirate_shipQ) > 0:
                # self.status()
                # print("Non Empty Queue")
                q3.acquire()
                # print("In Q for PSQ: ", len(self.pirate_shipQ))
                # print("In Q for PS: ", len(self.ps.attendees))
                # print("Current Q in PS: ", self.ps.queue_capacitiy)
                if len(self.ps.attendees) == self.ps.queue_capacitiy:
                    # print("PS Q is full")
                    q3.release()
                else:
                    # print("Adding to PS Q.")
                    self.pirate_shipQ[0].exit_time = datetime.now().time()

                    # loggear
                    self.pirate_shipQ[0].log_entry('ZonaComun.txt', common_zone_log_sem)

                    self.pirate_shipQ[0].start_time = datetime.now().time()
                    self.ps.attendees.append(self.pirate_shipQ[0])
                    del self.pirate_shipQ[0]
                    q3.release()
                    time.sleep(1)


    def send_to_sr_queue(self):

        while True:
            # print("IF THIS CHANGES THE SR IS WORKING: ", len(self.sr.attendees))
            if len(self.shooting_rangeQ) == 0:
                # self.status()
                global start_sr_q
                # print("Empty Queue")
                start_sr_q = 1
                sr_q_sem.acquire()

            if len(self.shooting_rangeQ) > 0:
                # self.status()
                # print("Non Empty Queue")
                q4.acquire()
                # print("In Q for SRQ: ", len(self.shooting_rangeQ))
                # print("In Q for SR: ", len(self.sr.attendees))
                # print("Current Q in SR: ", self.sr.queue_capacitiy)
                if len(self.sr.attendees) == self.sr.queue_capacitiy:
                    # print("SR Q is full")
                    q4.release()
                else:
                    # print("Adding to SR Q.")
                    self.shooting_rangeQ[0].exit_time = datetime.now().time()

                    # loggear
                    self.shooting_rangeQ[0].log_entry('ZonaComun.txt' ,common_zone_log_sem)
                    self.shooting_rangeQ[0].start_time = datetime.now().time()
                    self.sr.attendees.append(self.shooting_rangeQ[0])
                    del self.shooting_rangeQ[0]
                    q4.release()
                    time.sleep(1)

if __name__ == '__main__':

    #Lista para los clientes

    customers_list = []

    #Se genera la zona comun con su respectivo Thread
    cz = CommonZone()
    cz.start_common_zone_thread()

    #Juegos posibles!
    games = [RC, HH, PS, SR]
    # print("Adding Customers")
    for i in range(150):
        customers_list.append(Customer("Fabo "+str(i+1), games[ran.randint(0,3)]))

    for c in customers_list:
        t = threading.Thread(target = cz.queue_people, args=(c,))
        t.start()
