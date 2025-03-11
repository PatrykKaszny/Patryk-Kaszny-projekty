function loadConsumedProductsTable() {
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState === 4 && this.status === 200) {
            const responseHTML = this.responseText;

            // Wstaw dane do tabeli
            document.getElementById("consumedProductsTable").innerHTML = responseHTML;

            // Zaktualizuj podsumowanie (jeśli sumy są zawarte w odpowiedzi HTML)
            const totalsRow = document.querySelector('.totals');
            if (totalsRow) {
                document.getElementById("totalProtein").textContent = totalsRow.cells[2].textContent;
                document.getElementById("totalCarb").textContent = totalsRow.cells[3].textContent;
                document.getElementById("totalFat").textContent = totalsRow.cells[4].textContent;
                document.getElementById("totalKcal").textContent = totalsRow.cells[5].textContent;
            }
        }
    };

    xhttp.open("GET", "consumedProductsData", true);
    xhttp.send();
}

document.addEventListener('DOMContentLoaded', function () {
    const table = document.getElementById('eatenProductsTable');
    
    table.addEventListener('click', function (event) {
        if (event.target.classList.contains('delete-btn')) {
            const productName = event.target.dataset.name;

            // Wyślij żądanie do serwera, aby usunąć produkt
            fetch('consumedProductsData', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: new URLSearchParams({
                    action: 'delete',
                    name: productName
                })
            })
            .then(response => response.text())
            .then(message => {
                console.log(message);

                // Usuń wiersz z tabeli
                const row = event.target.closest('tr');
                row.remove();
            })
            .catch(error => {
                console.error('Błąd podczas usuwania:', error);
            });
        } else if (event.target.classList.contains('edit-btn')) {
            const productName = event.target.dataset.name;

            // Wyświetl prompt do wprowadzenia nowej wagi
            const newWeight = prompt(`Podaj nową wagę dla produktu "${productName}":`);
            if (newWeight) {
                // Wyślij żądanie do serwera, aby zmodyfikować wagę produktu
                fetch('consumedProductsData', {
                    method: 'POST',
                    headers: {
                        'Content-Type': 'application/x-www-form-urlencoded',
                    },
                    body: new URLSearchParams({
                        action: 'edit',
                        name: productName,
                        weight: newWeight
                    })
                })
                .then(response => response.json()) // Zakładamy, że serwer zwraca JSON z aktualnymi danymi
                .then(data => {
                    console.log(data.message);

                    // Zaktualizuj wartości w tabeli (jeśli żądanie zakończyło się sukcesem)
                    const row = event.target.closest('tr');
                    const weightCell = row.querySelector('td:nth-child(2)');
                    const proteinCell = row.querySelector('td:nth-child(3)');
                    const kcalCell = row.querySelector('td:nth-child(4)');
                    const fatCell = row.querySelector('td:nth-child(5)');
                    const carbCell = row.querySelector('td:nth-child(6)');

                    weightCell.textContent = `${data.weight} g`;
                    proteinCell.textContent = `${data.protein} g`;
                    kcalCell.textContent = `${data.kcal} kcal`;
                    fatCell.textContent = `${data.fat} g`;
                    carbCell.textContent = `${data.carb} g`;
                })
                .catch(error => {
                    console.error('Błąd podczas modyfikacji:', error);
                });
            }
        }
    });
});