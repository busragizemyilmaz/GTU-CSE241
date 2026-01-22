#include <iostream>
#include <cstdlib>  // For rand() and srand()
#include <ctime>  // For time()
#include <vector> // For vector management
#include <string>

// Tüm gerekli sınıf başlık dosyalarını dahil et
#include "Cell.h"
#include "ConnectFourAbstract.h" 
#include "ConnectFourPlus.h"
#include "ConnectFourDiag.h"
#include "ConnectFourPlusUndo.h"

using namespace Game;
using std::cout;
using std::endl;
using std::cerr;
using std::string;
using std::vector;

int main() 
{
    // Rastgele sayı üretecini başlat (Bilgisayar hamleleri için)
    srand(time(NULL)); 

    cout << "--- CSE 241 HW #4: Simplified Test ---" << endl;

    // --- 1. Sınıf Nesnelerini Oluştur (Basit Test İçin Sadece İki Oyun) ---
    
    // Test 1: ConnectFourPlus (Yatay/Dikey Kazanma Kuralı)
    // 6x6 tahta
    ConnectFourPlus game1(6, 6); 

    // Test 2: ConnectFourDiag (Çapraz Kazanma Kuralı)
    // 5x5 tahta
    ConnectFourDiag game2("file2.txt"); 

    // Polimorfizm için temel sınıf işaretçileri kullanıyoruz
    vector<ConnectFourAbstract*> games;
    games.push_back(&game1);
    games.push_back(&game2);
    
    // --- 2. Basitleştirilmiş Oyun Döngüsü (Her oyuncu 2'şer kez oynar) ---
    
    cout << "\n--- Starting Simplified Game Play (2 Moves Per Player) ---\n";
    
    // User1 = 'X', User2 = 'O'
    CellState user1 = CellState::user1;
    CellState user2 = CellState::user2;
    
    // Oyun adımları: X oynar, O oynar, X oynar, O oynar.
    int totalSteps = 4; 
    
    for (int step = 1; step <= totalSteps; ++step) 
    {
        CellState currentPlayer = (step % 2 != 0) ? user1 : user2; // Tek adımda User1 (X), Çift adımda User2 (O)
        char colToPlay = (step % 2 != 0) ? 'a' : 'b'; // X -> 'a' sütununa, O -> 'b' sütununa

        cout << "\n==========================================";
        cout << "\nSTEP " << step << " | Current Player: " << (currentPlayer == user1 ? "User 1 (X)" : "User 2 (O)") << endl;
        
        for (size_t i = 0; i < games.size(); ++i) {
            ConnectFourAbstract* currentGame = games[i];
            
            cout << "Board " << i + 1 << " status:\n";
            currentGame->printBoard();
            
            if (currentGame->isGameEnded()) {
                cout << "   !!! GAME ALREADY ENDED !!!\n";
                continue;
            }

            // Hamleyi yap
            if (currentGame->play(colToPlay, currentPlayer)) {
                cout << "   -> Played successfully in column '" << colToPlay << "'.\n";
            } else {
                cout << "   -> Could not play in column '" << colToPlay << "'.\n";
            }
        }
    }

    // --- 3. Sonuçları Dosyaya Kaydet (aftergame1.txt, aftergame2.txt) ---
    
    cout << "\n--- Saving Final Game States ---\n";

    // Oyun 1'in sonucunu kaydet
    games[0]->writeToFile("aftergame1.txt");
    cout << "-> Final state of Game 1 saved to aftergame1.txt" << endl;

    // Oyun 2'nin sonucunu kaydet
    games[1]->writeToFile("aftergame2.txt");
    cout << "-> Final state of Game 2 saved to aftergame2.txt" << endl;


    // --- 4. Dinamik Belleği Temizle ---
    // Not: Bu testte dinamik bellek (new) ile oluşturulmadığı için (stack'te tanımlandı), 
    // sadece vector'ün içindeki referanslar silinir.
    games.clear(); 

    cout << "\nProgram finished successfully.\n";
    return 0;
}