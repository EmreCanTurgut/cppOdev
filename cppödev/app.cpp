#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <iomanip>
#include <stdexcept>

using namespace std;

class Student {
private:
    string* names;
    string* studentNumbers;
    float* midterms;
    float* secondExams;
    float* homeworks;
    float* finals;
    int* attendanceCounts;
    float* averages;

    int studentCount;

public:
    Student();
    ~Student();
    void readFromCSV(const string& filename);
    void average();
    void print(int option = -1, const string& outputFile = "");
};

/*
Student::Student() : names(nullptr), studentNumbers(nullptr), midterms(nullptr),
                     secondExams(nullptr), homeworks(nullptr), finals(nullptr),
                     attendanceCounts(nullptr), averages(nullptr), studentCount(0) {}
*/
Student::Student() {
    names = nullptr;
    studentNumbers = nullptr;
    midterms = nullptr;
    secondExams = nullptr;
    homeworks = nullptr;
    finals = nullptr;
    attendanceCounts = nullptr;
    averages = nullptr;
    studentCount = 0;
}

// Destructor
Student::~Student() {
    delete[] names;
    delete[] studentNumbers;
    delete[] midterms;
    delete[] secondExams;
    delete[] homeworks;
    delete[] finals;
    delete[] attendanceCounts;
    delete[] averages;
}

// readFromCSV function
void Student::readFromCSV(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Dosya acilamadi: " << filename << endl;
        return;
    }

    string line;

    int count = 0;
    while (getline(file, line)) {
        count++;
    }
    file.clear();
    file.seekg(0);
   

    studentCount = count;

    names = new string[studentCount];
    studentNumbers = new string[studentCount];
    midterms = new float[studentCount];
    secondExams = new float[studentCount];
    homeworks = new float[studentCount];
    finals = new float[studentCount];
    attendanceCounts = new int[studentCount];
    averages = new float[studentCount];

    int i = 0;
    while (getline(file, line)) {
        stringstream ss(line); // getline direk string üzerinde çalışmaz, stringstream üzerinde çalışır
        string value;

        try {
            // getline 3 parametresi şunlardır(okuma yapılcak yer,kaydedilcek yer, sınırladnırma yapılcak yer )
            getline(ss, names[i], ','); 
            getline(ss, studentNumbers[i], ',');

            getline(ss, value, ','); 
            midterms[i] = stof(value);// veriyi float türüne çevirip diziye ekle

            getline(ss, value, ',');
            secondExams[i] = stof(value); // veriyi float türüne çevirip diziye ekle

            getline(ss, value, ',');
            homeworks[i] = stof(value); // veriyi float türüne çevirip diziye ekle

            getline(ss, value, ',');
            finals[i] = stof(value); // veriyi float türüne çevirip diziye ekle

            getline(ss, value, ',');
            attendanceCounts[i] = stoi(value); // veriyi int türüne çevirip diziye ekle
        } catch (const invalid_argument& e) {
            cerr << "Gecersiz veri bulundu. Satir atlandi.\n";
            continue;
        }
        i++;
    }
    file.close();
}


void Student::average() {
    cout<<"---ORTALAMA---\n";
    for (int i = 0; i < studentCount; i++) {
        averages[i] = midterms[i] * 0.2f + secondExams[i] * 0.2f +
                      homeworks[i] * 0.2f + finals[i] * 0.4f;
    }
    for (int i = 0; i < studentCount; i++) {
        
    cout << names[i] << " ortlama :"<< averages[i]<<"\n";
    }
}


void Student::print(int option, const string& outputFile) {
    ostream* out;
    ofstream file; // dosyaya yazmak için

// outputFile parametresi boş değilse dosya açmaya çalışılır
    if (!outputFile.empty()) {
        file.open(outputFile);
        if (!file.is_open()) {
            cerr << "Dosya acilamadi: " << outputFile << endl;
            return;
        }
     // eğer ikinci parametre varsa out yazma işlemi olarak çalışır yoksa okuma
        out = &file;
    } else {
        out = &cout;
    }

    if (option == -1) {
        *out << "Tum Ogrenciler:\n";
        for (int i = 0; i < studentCount; i++) {
            *out << "Ad: " << names[i] 
                 << ", Numara: " << studentNumbers[i] 
                 << ", Vize: " << midterms[i] 
                 << ", 2. Sinav: " << secondExams[i] 
                 << ", Odev: " << homeworks[i] 
                 << ", Final: " << finals[i] 
                 << ", Yoklama: " << attendanceCounts[i] <<"\n";
                
        }
    } else if (option == 0) {
        *out << "Kalan Ogrenciler:\n";
        for (int i = 0; i < studentCount; i++) {
            if (averages[i] < 50.0f) {
                *out << "Ad: " << names[i] 
                     << ", Numara: " << studentNumbers[i]
                    << ", Vize: " << midterms[i] 
                 << ", 2. Sinav: " << secondExams[i] 
                 << ", Odev: " << homeworks[i] 
                 << ", Final: " << finals[i] 
                 << ", Yoklama: " << attendanceCounts[i]<<"\n" ;
                                }
        }
    } else if (option == 1) {
        *out << "Gecen Ogrenciler:\n";
        for (int i = 0; i < studentCount; i++) {
            if (averages[i] >= 50.0f) {
                *out << "Ad: " << names[i] 
                     << ", Numara: " << studentNumbers[i]
                     << ", Vize: " << midterms[i] 
                 << ", 2. Sinav: " << secondExams[i] 
                 << ", Odev: " << homeworks[i] 
                 << ", Final: " << finals[i] 
                 << ", Yoklama: " << attendanceCounts[i]<<"\n" ;
                    
            }
        }
    }

    if (file.is_open()) {
        file.close();
    }
}

int main() {
    Student studentList;

    studentList.readFromCSV("girdi.csv");

    // Tum ogrencileri ve özelliklerini yazdirir
    //studentList.print();
    
    // Tum ogrencilerin not ortalaması
   studentList.average();


    // Kalan ogrencileri yazdirir
    //studentList.print(0);

    // Gecen ogrencileri yazdirir
    //studentList.print(1);

    // Tum ogrencileri dosyaya yazar
    studentList.print(-1, "sonuclar.csv");

    return 0;
}
