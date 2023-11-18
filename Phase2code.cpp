
#include <bits/stdc++.h>

using namespace std;

int IC, PTR, VA, RA, flag[30], PI, TI, SI;

char M[300][4], IR[4], R[4];

bool C;

fstream fin, fout;

string line;

struct PCB{
    int job, TTL, TLL, TTC, TLC;
}pcb;

//function used

//intailize the program
void init()
{
    for(int i=0; i<300; i++)
    {
        for(int j=0; j<4; j++)
        {
            M[i][j]= ' ';
        }
    }

    //initlize that block in mm is occupied or not
    for(int i = 0; i < 30; i++){
        flag[i] = 0;
    }

    IR[4] = {'-'};       //instruction register to -
    R[4] = {'-'};       //Register to -
    IC = 0;            //instruction counter to 0
    C = false;
    PTR = 0;            //page table register
    VA = 0;             //virtual address
    RA = 0;             //Real address
    PI = 0;             //program interrupt
    TI = 0;             //time interrupt

}


//random number between 0 to 29 for storing the program in mm
int allocate()
{
    return (rand() % 30);
}
//memory mapping function that maps the virtual address with the real address
int AddMap(int reg)
{
    int PTE = PTR * 10 + reg / 10;   //page table entry
    cout<<"PTE: "<<PTE<<endl;
    string temp = "";

    //if page table is NULL
    if(M[PTE][0] == '*')
    {
        cout<<"**** Page fault occured ****\n";
        return -1;
    }
    else{
        for(int  i = 0; i < 4; i++){
            if(M[PTE][i] != ' '){
                temp += M[PTE][i];
            }
        }
        int data = (stoi(temp) * 10) + (reg % 10);
        cout<<"Data = "<<data<<endl;
        return data;
    }
}


void status(){
    fout<<"\nJob ID: "<<pcb.job<<"\tSI: "<<SI<<"\tTI: "<<TI<<"\tPI: "<<PI<<"\tTTC : "<<pcb.TTC<<"\tLLC: "<<pcb.TLC<<"\tIR: ";
    for(int i = 0; i < 4; i++){
         fout<<IR[i];
    }
    fout<<"\n\n";
}

void endprogram()
{
    fout<<"\n---PROGRAM TERMINATED ABNORMALLY---"<<endl;

}

void MOS()
{

    if(SI==1)
    {
        getline(fin, line);

        if(line[0] == '$' && line[1] == 'E' && line[2] == 'N' && line[3] == 'D'){
            endprogram();
            fout<<"Error: Out of Data "<<endl;
            return;
        }

        int frame = allocate();
        cout<<"Frame = "<<frame<<endl;
        while (flag[frame] != 0){
            frame = allocate();
        }

        flag[frame] = 1;

        int i = PTR;
        i = i * 10;
        cout << "\n\nPTR = " << PTR << endl;
        while (M[i][0] != '*'){
            i++;
        }


        M[i][0] = ' ';
        M[i][1] = ' ';
        M[i][2] = (frame / 10) + 48;
        M[i][3] = frame % 10 + 48;

        int l = 0;
        frame = frame * 10;
        for (int i = 0; i < line.length() && line.length() < 40; i++){
            M[frame][l++] = line[i];
            if (l == 4){
                l = 0;
                frame += 1;
            }
        }
    }
    else if(SI==2){
        pcb.TLC += 1;
        if (pcb.TLC > pcb.TLL){
            endprogram();
            fout<<"Error: Line Limit Exceed"<<endl;
            return;
        }

        int add = IR[2] - 48;
        add = (add * 10);

        RA = AddMap(add);

        if (RA != -1){
            string out;

            for (int i = 0; i < 10; i++){
                for (int j = 0; j < 4; j++){
                    out += M[RA][j];
                }
                RA += 1;
            }
            fout << out << "\n";
        }else{
            endprogram();
            PI = 3;
            fout<<"Error ( PI = 3 ): Invalid Page Fault"<<endl;
        }
    }else if(SI==3){
        fout<<"\nProgram Terminated Successfully"<<endl;
        status();
    }
}

void executeProgram()
{
    while(1){
        if (PI != 0 || TI != 0 ){
            fout<< "JOBID: "<<pcb.job<<"\tIC: "<<IC<<"\tToggle : "<<C<<"\tTLC: "<<pcb.TLC<<"\tTTC: "<<pcb.TTC<<"\tTTL: "<<pcb.TTL<<"\tTLL: " <<pcb.TLL<<"\tIR: ";
            for (int i = 0; i < 4; i++){
                fout << IR[i];
            }
            fout<<"\n\n";
            break;
        }

        cout<<"IC="<<IC<<endl;
        RA = AddMap(IC);
        cout<<"RA: "<<RA<<endl;

        if(M[RA][0] != 'H' && (!isdigit(M[RA][2]) || !isdigit(M[RA][3]))){
            endprogram();
            // PI = 2;
            fout<<"Error ( PI = 2 ): Oprand Error";
            status();
        }
        for (int i = 0; i < 4; i++){
            IR[i] = M[RA][i];
        }
        IC++;

        int add = ((IR[2] - 48) * 10) + (IR[3] - 48);
        cout<<"Address: "<<add<<endl;

        //check the errors for TI
        if((IR[0] == 'G' && IR[1] == 'D') || (IR[0] == 'S' && IR[1] == 'R')){
            pcb.TTC += 2;
        }
        else{
            pcb.TTC +=1;
        }
        if(pcb.TTC > pcb.TTL){
            TI = 2;
            endprogram();
            fout<<"Error ( TI = 2 )= Time Limit Exceed";
            status();
            break;
        }

        //check for the PI errors
        if(IR[0] == 'L' && IR[1] == 'R'){
            int RA = AddMap(add);
            cout<<"RA: "<<RA<<endl;
            if(RA = -1){
                endprogram();
                // PI = 3;
                fout<<"Error ( PI = 3 ): Invalid Page Fault";
            }
            else{
                for(int i = 0; i < 4; i++){
                    R[i] = M[RA][i];
                }
            }
        }
        else if(IR[0] == 'S' && IR[1] == 'R'){
                int RA = AddMap(add);
                cout<<"RA: "<<RA<<endl;
                if(RA = -1){
                    for(int i = 0; i < 4; i++){
                        M[RA][i] = R[i];
                    }
                }
                else{
                    int frame = allocate();
                    while (flag[frame] != 0){
                        frame = allocate();
                    }

                    flag[frame] = 1;

                    int i = PTR;
                    i = i * 10;
                    while (M[i][0] != '*'){
                        i++;
                    }


                    M[i][0] = ' ';
                    M[i][1] = ' ';
                    M[i][2] = (frame/10) + 48;
                    M[i][3] = frame % 10 + 48;

                    frame = frame * 10;
                    for (int i = 0; i < 4; i++){
                        M[frame][i] = R[i];
                    }
                }
            }
            else if(IR[0] == 'C' && IR[1] == 'R'){
                int b = 0;
                int RA = AddMap(add);
                cout<<"RA: "<<RA<<endl;
                if(RA = -1){
                    endprogram();
                    PI = 3;
                    fout<<"Error ( PI = 3 ): Invalid Page Fault";
                }
                else{
                    for(int i = 0; i < 4; i++){
                        if(R[i] != M[RA][i]){
                            b = 1;
                        }
                    }

                    if(b == 1){
                        C = false;
                    }
                    else{
                        C = true;
                    }
                }
            }
            else if(IR[0] == 'B' && IR[1] == 'T'){
                if(C == true){
                    IC = add;
                }
            }
            else if(IR[0] == 'G' && IR[1] == 'D'){
                SI= 1;
                MOS();
            }
            else if(IR[0] == 'P' && IR[1] == 'D'){
                SI= 2;
                MOS();
            }
            else if(IR[0] == 'H'){
                SI= 3;
                MOS();
                break;
            }
            else{
                endprogram();
                // PI = 1;
                fout<<"Error ( PI = 1 ): Opcode Error";
                status();
                break;
            }
        }
}

//load in memory
void load()
{
    cout<<"\n Reading Lines...."<<endl;
    while(getline(fin, line))
    {

        cout<<line<<endl;
        if(line[0] =='$' && line[1]=='A' && line[2]=='M' && line[3]=='J')
        {
            init();
            PTR = allocate();     //page table register holds the location of the page table in mm
            cout<<"PTR : "<<PTR<<endl;
            //store * at page table location in mm
            for(int i = PTR * 10; i < PTR *10 + 10; i++){
                for(int j = 0; j < 4 ; j++){
                    M[i][j] = '*';
                }
            }
            flag[PTR] = 1;

            //initialize pcb
            pcb.TTC=0, pcb.TLC=0;
            string job_id = "", ttl = "", tll = "";
            int i;
            //get job id
            for(i=4;i<8;i++){
                job_id += line[i];
            }
            //get total time limit
            for(i=8;i<12;i++){
                ttl += line[i];
            }
            //get total line limit
            for(i=12;i<16;i++){
                tll += line[i];
            }

            //ttl and tll in numeric value
            pcb.job = stoi(job_id);
            pcb.TTL = stoi(ttl);
            pcb.TLL = stoi(tll);
            cout<<" Job ID: "<<pcb.job<<endl;
            cout<<" TTL:  "<<pcb.TTL<<endl;
            cout<<" TLL:  "<<pcb.TLL<<endl;

        }
        else if(line[0] =='$' && line[1]=='D' && line[2]=='T' && line[3]=='A')
        {
            IC = 0;
            executeProgram();
        }
        else if(line[0] =='$' && line[1]=='E' && line[2]=='N' && line[3]=='D')
        {
            for(int i = 0; i < 300; i++){
                cout<<"\nM["<<i<<"] - ";
                for(int j = 0; j< 4; j++){
                    cout<<M[i][j]<<" ";
                }
            }
            cout<<"\n---------HALT EXECUTION---------\n";
        }
        else{                         //program card
            int frame = allocate();
           // cout<<"Frame no: "<<frame<<endl;
            //till getting an empty frame
            while(flag[frame] != 0){
                frame = allocate();
                cout<<"Frame no: "<<frame<<endl;
            }

            flag[frame] = 1;
            int a = PTR;
            //storing the contents in page table first
            while(M[a][0] != '*'){
                a++;
            }

            M[a][0] = ' ';
            M[a][1] = ' ';
            M[a][2] = (frame / 10) + 48;   //(48 = 0) to store at appropriate location starting from 0
            M[a][3] = (frame  % 10) + 48;

            int len = 0;
            for(int  i = frame * 10; i < frame * 10 + 10 && len < line.length(); i++){
                for(int j = 0; j < 4; j++){
                    if(line[len] =='H'){
                        M[i][j] = line[len++];
                        break;
                    }
                    else{
                        M[i][j] = line[len++];
                    }
                }
            }
            line.clear();
        }
    }
}


int main()
{
    fin.open("inputp2.txt", ios::in);
    fout.open("outputp2.txt", ios::out);
    load();
    return 0;
}
