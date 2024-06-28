# online-exam-system
online exam system is an online system where it manipulates grades of subjects taken online and any irregularity
In this system, the Exam class has three member variables: examID, subject, and duration, which are common attributes of all exams.
The gradeExam function is declared as a pure virtual function.
Additionally, I've included getter functions for each attribute, which allow access to the exam's properties.
Note that I've used const to ensure that the getter functions do not modify the object's state, and the gradeExam function is declared as const to indicate that it does not modify the object's state either.

here is the code for question (a)

#include <string>

class Exam {
protected:
    std::string examID;
    std::string subject;
    int duration; // in minutes

public:
    Exam(const std::string& id, const std::string& subj, int dur)
        : examID(id), subject(subj), duration(dur) {}

    // Pure virtual function to be implemented in derived classes
    virtual double gradeExam() const = 0;

    // Getter functions for exam attributes
    std::string getExamID() const { return examID; }
    std::string getSubject() const { return subject; }
    int getDuration() const { return duration; }
};

Here's an implementation of constructors and destructors for the Exam class and its derived classes:
#include <string>

class Exam {
protected:
    std::string examID;
    std::string subject;
    int duration; // in minutes

public:
    Exam(const std::string& id, const std::string& subj, int dur)
        : examID(id), subject(subj), duration(dur) {}

    virtual ~Exam() {} 

    // Pure virtual function 
    virtual double gradeExam() const = 0;

    std::string getExamID() const { return examID; }
    std::string getSubject() const { return subject; }
    int getDuration() const { return duration; }
};

class MultipleChoiceExam : public Exam {
private:
    int numQuestions;
    int numCorrect;

public:
    MultipleChoiceExam(const std::string& id, const std::string& subj, int dur, int numQues)
        : Exam(id, subj, dur), numQuestions(numQues), numCorrect(0) {}

    ~MultipleChoiceExam() {} 

    void setNumCorrect(int correct) { numCorrect = correct; }

    double gradeExam() const override {
        return static_cast<double>(numCorrect) / numQuestions * 100.0;
    }
};

class EssayExam : public Exam {
private:
    std::string essayAnswer;

public:
    EssayExam(const std::string& id, const std::string& subj, int dur)
        : Exam(id, subj, dur), essayAnswer("") {}

    ~EssayExam() {} // Destructor, no dynamic memory to release

    void setEssayAnswer(const std::string& answer) { essayAnswer = answer; }

    double gradeExam() const override {
        // Essay grading logic goes here, for demonstration purposes, return a fixed grade
        return 85.0;
    }
};

The Exam class has a constructor that initializes its member variables and a virtual destructor to ensure proper cleanup.
------------------------------------------------------------------------------------------------------------------------
Here's the implementation of the gradeExam function in MultipleChoiceExam


class MultipleChoiceExam : public Exam {
private:
    int numQuestions;
    int numCorrect;

public:
    MultipleChoiceExam(const std::string& id, const std::string& subj, int dur, int numQues)
        : Exam(id, subj, dur), numQuestions(numQues), numCorrect(0) {}

    ~MultipleChoiceExam() {}

    void setNumCorrect(int correct) { numCorrect = correct; }

    double gradeExam() const override {
        if (numCorrect < 0 || numCorrect > numQuestions) {
            throw GradingErrorException("Number of correct answers is out of range.");
        }
        return static_cast<double>(numCorrect) / numQuestions * 100.0;
    }
};
----------------------------------------------------------------------------------------------------------------------------
Here's the implementation of the gradeExam function in MEssayExam

public:
    EssayExam(const std::string& id, const std::string& subj, int dur)
        : Exam(id, subj, dur), essayAnswer(""), score(0.0) {}

    ~EssayExam() {}

    void setEssayAnswer(const std::string& answer) { essayAnswer = answer; }

    void setScore(double score) {
        if (score < 0.0 || score > 100.0) {
            throw GradingErrorException("Score is out of range (0.0-100.0).");
        }
        this->score = score;
    }

    double gradeExam() const override {
        return score;
    }
};
this is the implementation of the gradeExam function in both MultipleChoiceExam and EssayExam classes, as well as the incorporation of exception handling:
#include <iostream>
#include <stdexcept>
#include <random>


// Custom exception classes
class InvalidExamDurationException : public std::runtime_error {
public:
    InvalidExamDurationException(const std::string& msg) : std::runtime_error(msg) {}
};

class GradingErrorException : public std::runtime_error {
public:
    GradingErrorException(const std::string& msg) : std::runtime_error(msg) {}
};

class Exam {
protected:
    std::string examID;
    std::string subject;
    int duration; // in minutes

public:
    Exam(const std::string& id, const std::string& subj, int dur)
        : examID(id), subject(subj), duration(dur) {
        if (duration <= 0) {
            throw InvalidExamDurationException("Exam duration must be greater than 0 minutes.");
        }
    }

    virtual ~Exam() {}

    // Pure virtual function to be implemented in derived classes
    virtual double gradeExam() const = 0;

    // Getter functions for exam attributes
    std::string getExamID() const { return examID; }
   string getSubject() const { return subject; }
    int getDuration() const { return duration; }
};

class MultipleChoiceExam : public Exam {
private:
    int numQuestions;
    int numCorrect;

public:
    MultipleChoiceExam(const std::string& id, const std::string& subj, int dur, int numQues)
        : Exam(id, subj, dur), numQuestions(numQues), numCorrect(0) {}

    ~MultipleChoiceExam() {}

    void setNumCorrect(int correct) { numCorrect = correct; }

    double gradeExam() const override {
        if (numCorrect < 0 || numCorrect > numQuestions) {
            throw GradingErrorException("Number of correct answers is out of range.");
        }
        return static_cast<double>(numCorrect) / numQuestions * 100.0;
    }
};

class EssayExam : public Exam {
private:
    std::string essayAnswer;
    mutable double score; // make score mutable for grading

public:
    EssayExam(const std::string& id, const std::string& subj, int dur)
        : Exam(id, subj, dur), essayAnswer(""), score(0.0) {}

    ~EssayExam() {}

    void setEssayAnswer(const std::string& answer) { essayAnswer = answer; }

    void grade(const double score) {
        if (score < 0.0 || score > 100.0) {
            throw GradingErrorException("Score is out of range (0.0-100.0).");
        }
        this->score = score;
    }

    double gradeExam() const override {
        return score;
    }
};

int main() {
    try {
        MultipleChoiceExam mcExam("MCE101", "Math", 60, 10);
        mcExam.setNumCorrect(8);
        std::cout << "Multiple Choice Exam Grade: " << mcExam.gradeExam() << "%" << std::endl;

        EssayExam essayExam("EE101", "English", 90);
        essayExam.setEssayAnswer("This is a sample essay answer.");
        essayExam.grade(85.0);
        std::cout << "Essay Exam Grade: " << essayExam.gradeExam() << "%" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}


-----------------------------------------------------------------------------------------------------------------------
In the main function, I've demonstrated the usage of the gradeExam function for both MultipleChoiceExam and EssayExam classes, and also handled exceptions using a try-catch block.

int main() {
    try {
        MultipleChoiceExam mcExam("MCE101", "Math", 60, 10);
        mcExam.setNumCorrect(8);
        std::cout << "Multiple Choice Exam Grade: " << mcExam.gradeExam() << "%" << std::endl;

        EssayExam essayExam("EE101", "English", 90);
        essayExam.setEssayAnswer("This is a sample essay answer.");
        essayExam.grade(85.0);
        std::cout << "Essay Exam Grade: " << essayExam.gradeExam() << "%" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}
here is an example of the feedback of my code

![Screenshot from 2024-06-28 11-02-37](https://github.com/frostyq2017/online-exam-system/assets/143500168/2f5f42ce-bc22-4e5c-9317-a04b72fa59b2)
