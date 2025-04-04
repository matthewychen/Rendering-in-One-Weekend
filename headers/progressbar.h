void progressbar(int maxline, int currline) {
    constexpr int barlength = 50;
    double currpos = double(currline)/maxline;
    int progress = int(currpos * barlength);
    char bardata[barlength + 1]{};
    for(int i = 0; i < progress; i++) {
        bardata[i] = (char)219;
    }
    for(int j = progress; j < barlength; j++) {
        bardata[j] = (char)177;
    }
    bardata[barlength] = '\0';

    // Clear the line and show current progress
    std::clog << "\rProgress: " << currline << "/" << maxline << " [" << bardata << "] " 
              << int(currpos * 100) << "%" << std::flush;
    
    // Add a newline when complete
    if(currline == maxline) {
        std::clog << "\rProgress: " << currline << "/" << maxline << " [" << bardata << "] " 
              << int(currpos * 100) << "%" << std::flush;
        std::clog << "\nDone.\n";
    }
}