#include <iostream>
#include <unistd.h>
#include <vector>
#include <sys/wait.h>
int process;
std::vector<std::string> names;

void processname(){
    std::string name;
    //demanem el nom
    std::cout << "Posa un nom: "  << "Process : " << getpid() << std::endl;
    std::cin >> name;
    //posem el nom en el vector
    names.push_back(name);
    //imprimim els valor contiguts en el array
    std::cout << "Valors en l'array: " << std::endl;
    for (auto name : names){
        std::cout << name << std::endl;
    }
    //escollim y imprimim el nom
    std::string chosed = names.at(rand() % (names.size()));
    std::cout << std::endl;
    std::cout << "Benvingut " << chosed << std::endl;
}
int main (int argc, char ** argv){
    //generem un semilla per escollir el nom aleatori
    srand(getpid());
    std::cout << "Quants procesos? " << std::endl;
    std::cin >> process;
    pid_t id;
    for (int i = 0 ; i < process ; i ++ ){
        id = fork();
        if (id == 0) {
            
            processname();
            //sortim del bucle perque la condició segueix sent certa i no interesa que
            //el mateix process executi la funció mes de una vegada,
            //aixi ens estaviem porcessos duplicats.
            // En el cas que aixi una iteració del bucle el fill crearia un altre fill y aquest fill tindria els valors del primer fill
            //ya que el primer fill actuaria com ha pare del fill,
            //pertant el vector contridria el valor inserit pel pare y pel fill
            // y podria donar la sensació de que els processos comparteixen memoria quan aixó es fals.
            //Per això tenim que auturar el bucle avans de hora.
            break;
        }
        if (id > 0) {
            pid_t pid = wait(NULL) ;
            std::cout << "acabat: " << pid << std::endl;
        }
    }
    
    
}
