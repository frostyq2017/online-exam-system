#include <iostream>
#include <stdexcept>
#include <random>
#include<string>

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