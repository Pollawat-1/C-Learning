#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <limits> // Required for numeric_limits (input buffer safety)

// === CLASS: DOCTOR ===
class Doctor {
public:
    std::string id;
    std::string name;
    std::string specialty;

    // Default constructor
    Doctor() {} 

    Doctor(std::string dId, std::string dName, std::string dSpec) {
        id = dId;
        name = dName;
        specialty = dSpec;
    }

    void display() const {
        std::cout << "Dr. " << name << " (" << specialty << ") [ID: " << id << "]" << std::endl;
    }
};

// === CLASS: PATIENT ===
class Patient {
public:
    int id;
    std::string name;
    std::string ailment;
    std::string doctorId;

    // FIX 1: Initialize ID to 0 to prevent random garbage numbers
    Patient() : id(0) {} 

    Patient(int pId, std::string pName, std::string pAilment, std::string docId) {
        id = pId;
        name = pName;
        ailment = pAilment;
        doctorId = docId;
    }

    void display() const {
        std::cout << "ID: " << id 
                  << " | Name: " << name 
                  << " | Issue: " << ailment 
                  << " | Doctor: " << doctorId << std::endl;
    }
};

// === GLOBAL LISTS ===
std::vector<Doctor> doctors;
std::vector<Patient> patients;

// === FILE HANDLING ===

void saveDoctors() {
    std::ofstream file("doctors.txt"); // Overwrite mode
    if (file.is_open()) {
        for (const auto& doc : doctors) {
            file << doc.id << "\n";
            file << doc.name << "\n";
            file << doc.specialty << "\n";
        }
        file.close();
    }
}

void loadDoctors() {
    std::ifstream file("doctors.txt");
    doctors.clear(); // Clear memory to avoid duplicates on reload

    if (file.is_open()) {
        Doctor temp;
        // We check if we can read the ID; if yes, we read the rest
        while (getline(file, temp.id)) {
            if (temp.id.empty()) continue; // Skip empty lines
            
            if (!getline(file, temp.name)) break;
            if (!getline(file, temp.specialty)) break;
            
            doctors.push_back(temp);
        }
        file.close();
    }
}

void savePatients() {
    std::ofstream file("patients.txt");
    if (file.is_open()) {
        for (const auto& pat : patients) {
            file << pat.id << "\n";
            file << pat.name << "\n";
            file << pat.ailment << "\n";
            file << pat.doctorId << "\n";
        }
        file.close();
    }
}

// FIX 2: Robust Loading Logic
void loadPatients() {
    std::ifstream file("patients.txt");
    patients.clear();

    if (file.is_open()) {
        Patient temp;
        std::string idStr;
        
        while (getline(file, idStr)) {
            // 1. Check if the line is empty (end of file cleanup)
            if (idStr.empty()) continue; 

            // 2. Safe conversion from String to Int
            try {
                temp.id = std::stoi(idStr);
            } catch (...) {
                continue; // If ID is corrupted text, skip this record
            }
            
            // 3. Read the next 3 lines. If ANY are missing, stop reading.
            // This prevents "partial" patients from being created.
            if (!getline(file, temp.name)) break;
            if (!getline(file, temp.ailment)) break;
            if (!getline(file, temp.doctorId)) break;

            patients.push_back(temp);
        }
        file.close();
    }
}

// === HELPER FUNCTIONS ===

bool doctorExists(std::string id) {
    for (const auto& doc : doctors) {
        if (doc.id == id) return true;
    }
    return false;
}

// === MENU FUNCTIONS ===

void addDoctor() {
    std::string id, name, spec;
    std::cout << "\n--- Add New Doctor ---" << std::endl;
    
    std::cout << "Enter Doctor ID (e.g. D01): ";
    std::cin >> id;
    
    // Clear buffer safely
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter Doctor Name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter Specialty: ";
    std::getline(std::cin, spec);

    doctors.push_back(Doctor(id, name, spec));
    saveDoctors(); 
    std::cout << "Doctor saved successfully." << std::endl;
}

void admitPatient() {
    int id;
    std::string name, ailment, docId = "UNASSIGNED";
    
    std::cout << "\n--- Admit New Patient ---" << std::endl;
    std::cout << "Enter Patient ID: ";
    
    // FIX 3: Input Validation Loop
    // This ensures the program doesn't crash if you type "abc" instead of a number
    while (!(std::cin >> id)) {
        std::cout << "Invalid input. Please enter a number: ";
        std::cin.clear(); 
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }
    
    // Clear the buffer so the next 'getline' works
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    std::cout << "Enter Patient Name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter Ailment: ";
    std::getline(std::cin, ailment);

    // Doctor Assignment
    std::cout << "Assign a doctor now? (y/n): ";
    char choice;
    std::cin >> choice;
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Clear buffer again
    
    if (choice == 'y' || choice == 'Y') {
        if (doctors.empty()) {
            std::cout << "No doctors available. Setting to UNASSIGNED." << std::endl;
        } else {
            std::cout << "Available Doctors: " << std::endl;
            for (const auto& doc : doctors) std::cout << "- " << doc.id << ": " << doc.name << std::endl;
            
            std::cout << "Enter Doctor ID: ";
            std::getline(std::cin, docId); // Use getline for ID to match format
            
            if (!doctorExists(docId)) {
                std::cout << "Doctor not found. Setting to UNASSIGNED." << std::endl;
                docId = "UNASSIGNED";
            }
        }
    }

    patients.push_back(Patient(id, name, ailment, docId));
    savePatients(); 
    std::cout << "Patient admitted and saved." << std::endl;
}

void viewAll() {
    std::cout << "\n=== HOSPITAL RECORDS ===" << std::endl;
    std::cout << "--- Doctors ---" << std::endl;
    if (doctors.empty()) std::cout << "No doctors found." << std::endl;
    for (const auto& doc : doctors) doc.display();

    std::cout << "\n--- Patients ---" << std::endl;
    if (patients.empty()) std::cout << "No patients found." << std::endl;
    for (const auto& pat : patients) pat.display();
}

// === MAIN ===
int main() {
    // Load data immediately
    loadDoctors();
    loadPatients();

    int choice;
    do {
        std::cout << "\n=== HOSPITAL MANAGEMENT SYSTEM ===" << std::endl;
        std::cout << "1. Add Doctor" << std::endl;
        std::cout << "2. Admit Patient" << std::endl;
        std::cout << "3. View All Records" << std::endl;
        std::cout << "4. Exit" << std::endl;
        std::cout << "Choice: ";
        
        // Input validation for menu choice
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cout << "Invalid input." << std::endl;
            continue;
        }

        switch(choice) {
            case 1: addDoctor(); break;
            case 2: admitPatient(); break;
            case 3: viewAll(); break;
            case 4: std::cout << "Exiting..." << std::endl; break;
            default: std::cout << "Invalid choice." << std::endl;
        }
    } while (choice != 4);

    return 0;
}