#include <string>
#include <fstream>
#include <stdexcept>
#include <iostream>

class IPrintable {
public:
    virtual ~IPrintable() = default;
    virtual std::string print() const = 0;
};

class IFormatter {
public:
    virtual ~IFormatter() = default;
    virtual std::string format(const std::string& data) const = 0;
};

class TextFormatter : public IFormatter {
public:
    std::string format(const std::string& data) const override {
        return data;
    }
};

class HTMLFormatter : public IFormatter {
public:
    std::string format(const std::string& data) const override {
        return "<html>" + data + "</html>";
    }
};

class JSONFormatter : public IFormatter {
public:
    std::string format(const std::string& data) const override {
        return "{ \"data\": \"" + data + "\"}";
    }
};

class Data : public IPrintable {
public:
    Data(std::string data, IFormatter* formatter)
        : data_(std::move(data)), formatter_(formatter) {}

    std::string print() const override {
        if (!formatter_) {
            throw std::runtime_error("Formatter is not set!");
        }
        return formatter_->format(data_);
    }

private:
    std::string data_;
    IFormatter* formatter_;
};

void saveTo(std::ofstream& file, const IPrintable& printable) {
    file << printable.print();
}

void saveToAsHTML(std::ofstream& file, const IPrintable& printable) {
    saveTo(file, printable);
}

void saveToAsJSON(std::ofstream& file, const IPrintable& printable) {
    saveTo(file, printable);
}

void saveToAsText(std::ofstream& file, const IPrintable& printable) {
    saveTo(file, printable);
}

int main() {
    TextFormatter textFormatter;
    HTMLFormatter htmlFormatter;
    JSONFormatter jsonFormatter;

    Data textData("Hello, World!", &textFormatter);
    Data htmlData("Hello, World!", &htmlFormatter);
    Data jsonData("Hello, World!", &jsonFormatter);

    std::ofstream textFile("output.txt");
    if (textFile.is_open()) {
        saveToAsText(textFile, textData);
        textFile.close();
    }

    std::ofstream htmlFile("output.html");
    if (htmlFile.is_open()) {
        saveToAsHTML(htmlFile, htmlData);
        htmlFile.close();
    }

    std::ofstream jsonFile("output.json");
    if (jsonFile.is_open()) {
        saveToAsJSON(jsonFile, jsonData);
        jsonFile.close();
    }

    return 0;
}
