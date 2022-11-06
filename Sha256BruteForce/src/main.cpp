#include "MenuHandler.h"

#include <QFile>
#include <QIODevice>
#include <QTextStream>
#include <QCryptographicHash>

void createDecryptionMap();

int main()
{
    createDecryptionMap();

    MenuHandler::execStartMenu();
    return 0;
}

void createDecryptionMap()
{
    if (QFile::exists("map.txt"))
        return;

    QFile map("map.txt");
    map.open(QIODevice::WriteOnly);

    QVector<QString> alphabet = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
                                 "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z"};

    QTextStream(stdout) << "Enumeration begins...\n";

    QMap<QString, QString> hashPairs;
    int alphabetSize = alphabet.size();

    for (int i = 0; i < alphabetSize; ++i)
    {
        for (int j = 0; j < alphabetSize; ++j)
        {
            for (int k = 0; k < alphabetSize; ++k)
            {
                for (int m = 0; m < alphabetSize; ++m)
                {
                    for (int n = 0; n < alphabetSize; ++n)
                    {
                        QString encryptedWord(alphabet[i] + alphabet[j] + alphabet[k] + alphabet[m] + alphabet[n]);
                        QString hash = QCryptographicHash::hash(encryptedWord.toUtf8(), QCryptographicHash::Sha256).toHex();

                        hashPairs.insert(hash, encryptedWord);
                    }
                }
            }
        }
    }

    QTextStream(stdout) << "Enumeration done\nCreating map...\n";

    QTextStream output(&map);

    for (const QString& key : hashPairs.keys())
        output << key + " " + hashPairs.value(key) + "\n";

    map.close();
}
