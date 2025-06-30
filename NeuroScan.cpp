#include <iostream>
#include <string>
#include <fstream>
#include <ctime>
#include <iomanip> // For formatting output (e.g., setw)
using namespace std;


/* NOTE: This is a symptom-based screening questions derived from research and clinical guidelines related to
   early signs of Alzheimer's disease, Parkinson's disease, and cognitive decline.

     Sources and References:
     - Alzheimer's Association. "10 Early Signs and Symptoms of Alzheimer's." https://www.alz.org/alzheimers-dementia/10_signs
     - Parkinson’s Foundation. "10 Early Warning Signs of Parkinson’s Disease." https://www.parkinson.org/Understanding-Parkinsons/10-Early-Warning-Signs
     - Mayo Clinic. "Mild cognitive impairment (MCI)." https://www.mayoclinic.org/diseases-conditions/mild-cognitive-impairment/symptoms-causes/syc-20354578
     - National Institute on Aging (NIA). https://www.nia.nih.gov/health

    These questions are simplified and intended for educational and awareness purposes,
    not for diagnosis. Users are encouraged to consult medical professionals for evaluation. */



// Constants and global variables
const int NUM_QUESTIONS = 10;               // Number of questions in the assessment
string logFile = "NeuroScan_Results.txt";  // File to save assessment results


/* Runs the NeuroScan assessment by asking symptom-related questions, recording responses,
   calculating the risk score, providing recommendations, saving results, and optionally
   setting reminders and accepting caregiver notes.

 * userName is the name of the user taking the assessment
 * isCaregiver is a boolean flag indicating if the assessment is being filled out by a caregiver. */



void runAssessment(string userName, bool isCaregiver)
{
    // Array of assessment questions
    string questions[NUM_QUESTIONS] =
    {
        "1. Do you often forget recent conversations, appointments, or events?",
        "2. Do you have trouble finding the right words during conversation?",
        "3. Do you get lost or confused in familiar places?",
        "4. Do you have trouble concentrating or following conversations with multiple people?",
        "5. Do you frequently misplace things and have trouble retracing your steps?",
        "6. Have you noticed stiffness or rigidity in your arms, legs, or neck?",
        "7. Do you walk more slowly or with a shuffling gait?",
        "8. Do you feel off-balance or experience frequent stumbling or unsteadiness?",
        "9. Have you noticed changes in your handwriting, such as smaller or shakier letters?",
        "10. Do you experience tremors or involuntary shaking when resting?"
    };

    int responses[NUM_QUESTIONS];  // Array to store user responses for each question
    int totalScore = 0;            // Variable to keep track of total risk score

    // Loop through each question, get user input, validate, and accumulate score
    for (int i = 0; i < NUM_QUESTIONS; i++)
    {
        cout << questions[i] << endl;
        cout << "Your response (0 = Never, 1 = Sometimes, 2 = Often): ";
        cin >> responses[i];

        // Input validation: ensure response is within valid range
        while (responses[i] < 0 || responses[i] > 2)
        {
            cout << "Invalid input. Please enter 0, 1, or 2: ";
            cin >> responses[i];
        }

        totalScore += responses[i]; // Add response value to total score

        // Display progress to user
        cout << "Progress: [" << setw(2) << i + 1 << "/" << NUM_QUESTIONS << "] completed\n\n";
    }

    cout << "------------------------------------------------------\n";

    // Special note for frequent memory issues (question 1 response = 2)
    if (responses[0] == 2)
    {
        cout << "\U0001F9E0 Additional Note: Frequent memory issues may be a sign of early cognitive decline.\n";
        cout << ">> Tip: Use reminders, sticky notes, and keep a memory journal.\n\n";
    }

    // Display user's total risk score out of the maximum possible score
    cout << userName << ", your total risk score is: " << totalScore << " out of " << NUM_QUESTIONS * 2 << ".\n";

    string riskLevel, recommendation; // Variables for risk classification and advice

    // Determine risk level and corresponding personalized recommendations based on total score
    if (totalScore >= 16)
    {
        riskLevel = "\U0001F534 High Concern";
        recommendation =
            "Your responses suggest significant symptoms. Please consult a healthcare professional.\n"
            ">> In the meantime: Keep a symptom journal, avoid multitasking, and ensure proper sleep.\n"
            "\nSupport Resources:\n- Alzheimer's Association: 1-800-272-3900 | https://www.alz.org/\n- Parkinson’s Foundation: https://www.parkinson.org";
    } else if (totalScore >= 9)
    {
        riskLevel = "\U0001F7E0 Moderate Concern";
        recommendation =
            "Some symptoms are present. A screening may be beneficial.\n"
            ">> Helpful habits: Brain games, exercise, and a Mediterranean diet.\n"
            "\nSupport Resources:\n- Cleveland Clinic Brain Health: https://my.clevelandclinic.org\n- AARP Brain Health: https://www.aarp.org/health/brain-health/";
    } else
    {
        riskLevel = "\U0001F7E2 Low Concern";
        recommendation =
            "No significant symptoms detected.\n"
            ">> Tip: Maintain a healthy lifestyle, engage socially, and stay mentally active.\n"
            "\nBrain Health Tips:\n- Try puzzles and memory games weekly\n- Stay physically active and socially engaged";
    }

    // Output the risk level and personalized recommendations to the user
    cout << "\n" << riskLevel << "\n" << recommendation << endl;

    // Get the current time for timestamping results
    time_t now = time(0);
    char* dt = ctime(&now);

    // Append assessment results with timestamp to the log file
    ofstream outFile(logFile, ios::app);
    outFile << "------------------------------------------\n";
    outFile << "User: " << userName << (isCaregiver ? " (Caregiver)" : "") << "\nDate: " << dt;
    outFile << "Score: " << totalScore << " / " << NUM_QUESTIONS * 2 << "\n";
    outFile << "Risk Level: " << riskLevel << "\n";
    outFile << "Recommendation: " << recommendation << "\n";
    outFile.close();

    cout << "\n\U0001F4C4 Your results have been saved to '" << logFile << "'.\n";
    cout << "------------------------------------------------------\n\n";

    // Prompt user to set a reminder for retaking the assessment after 1 or 2 weeks
    int reminderChoice;
    cout << "Would you like to set a reminder to retake this in:\n1 week (1), 2 weeks (2), or No reminder (0)? ";
    cin >> reminderChoice;
    if (reminderChoice == 1 || reminderChoice == 2)
    {
        // Calculate future time for reminder (in seconds)
        time_t future = now + reminderChoice * 7 * 24 * 60 * 60;
        char* reminderDate = ctime(&future);

        // Append reminder information to a separate reminders file
        ofstream reminderFile("NeuroScan_Reminders.txt", ios::app);
        reminderFile << userName << " should retake NeuroScan on: " << reminderDate;
        reminderFile.close();

        cout << "\n\U0001F514 Reminder saved! You'll see this in 'NeuroScan_Reminders.txt'.\n";
    }

    // Provide a weekly brain health challenge/tip to encourage healthy habits
    cout << "\n\U0001F4A1 Weekly Brain Health Challenge:\n";
    cout << "This week, try learning a new word each day and use it in conversation. 🧠📖\n";

    // Offer caregiver the option to leave a note related to the user's care
    if (isCaregiver)
    {
        string caregiverNote;
        cout << "\nWould you like to leave a caregiver note? (y/n): ";
        char noteChoice;
        cin >> noteChoice;
        cin.ignore(); // Clear newline from input buffer
        if (tolower(noteChoice) == 'y')
        {
            cout << "Enter your caregiver note: ";
            getline(cin, caregiverNote);

            // Append caregiver note to the results log file
            ofstream outFile(logFile, ios::app);
            outFile << "Caregiver Note: " << caregiverNote << "\n";
            outFile.close();
        }
    }
}

/* Reads and displays all past assessment results stored in the log file.
   If the file does not exist or is empty, informs the user accordingly. */


void viewPastResults()
{
    ifstream inFile(logFile);
    if (!inFile)
    {
        cout << "No previous results found.\n";
        return;
    }

    cout << "\n\U0001F4C1 Displaying past results:\n";
    cout << "------------------------------------------------------\n";

    string line;
    // Read and output each line from the log file until EOF
    while (getline(inFile, line))
    {
        cout << line << endl;
    }
    inFile.close();
}

int main()
{
    string userName;
    int choice;
    char caregiverInput;
    bool isCaregiver = false;

    // Greet the user and obtain their name
    cout << "Welcome to NeuroScan: Your Early Detection Assistant\n";
    cout << "------------------------------------------------------\n";
    cout << "Enter your name: ";
    getline(cin, userName);

    // Ask if the user is filling out the assessment on behalf of someone else (caregiver mode)
    cout << "Are you filling this out as a caregiver for someone else? (y/n): ";
    cin >> caregiverInput;
    cin.ignore(); // Clear newline from input buffer

    // Set caregiver mode flag based on user input
    if (tolower(caregiverInput) == 'y') isCaregiver = true;

    // Main menu loop allowing the user to take the assessment, view past results, or exit
    do
    {
        cout << "\n\U0001F44B Hello, " << userName << "! What would you like to do?\n";
        cout << "1. Take the NeuroScan Assessment\n";
        cout << "2. View Past Results\n";
        cout << "3. Exit\n";
        cout << "Enter your choice (1-3): ";
        cin >> choice;
        cin.ignore(); // Clear newline from input buffer

        switch (choice)
        {
            case 1:
                // Begin the assessment
                cout << "\nThis assistant will ask you 10 questions to evaluate early neurodegenerative symptoms.\n";
                cout << "Please answer honestly using the scale:\n";
                cout << "0 = Never\t1 = Sometimes\t2 = Often\n\n";
                runAssessment(userName, isCaregiver);
                break;
            case 2:
                // Display past results from log file
                viewPastResults();
                break;
            case 3:
                // Exit the program with a goodbye message
                cout << "\nThank you for using NeuroScan, " << userName << "! Stay healthy \U0001F499\n";
                break;
            default:
                // Handle invalid menu input
                cout << "Invalid choice. Please enter 1, 2, or 3.\n";
        }
    } while (choice != 3);

    return 0;
}
