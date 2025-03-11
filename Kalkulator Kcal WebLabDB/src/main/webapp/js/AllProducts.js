// Funkcja do załadowania listy produktów
function getAttendanceListTable(tableId) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState === 4 && this.status === 200) {
      document.getElementById(tableId).innerHTML = this.responseText;
    }
  };
  
  xhttp.open("GET", "attendanceList", true);
  xhttp.send();
}



function deleteProduct(productId) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState === 4 && this.status === 200) {
      // Po usunięciu produktu, odśwież tabelę
      getAttendanceListTable('tableAttendanceListId');
    }
  };

  // Wysłanie zapytania GET do serwera, aby usunąć produkt
  xhttp.open("GET", "attendanceList?id=" + productId, true);
  xhttp.send();
}

// Funkcja do edycji produktu
function editProduct(productId) {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState === 4 && this.status === 200) {
      // Wstawienie formularza modyfikacji w miejsce tabeli
      document.getElementById('tableAttendanceListId').innerHTML = this.responseText;
    }
  };

  xhttp.open("GET", "editProduct?id=" + productId, true);
  xhttp.send();
}


// Funkcja do wysłania formularza edycji
function submitEditForm() {
  var productId = document.getElementById('editProductForm').dataset.productId;
  var name = document.getElementById('editName').value;
  var protein = parseInt(document.getElementById('editProtein').value);
  var carb = parseInt(document.getElementById('editCarb').value);
  var fat = parseInt(document.getElementById('editFat').value);

  if (protein <= 0 || carb <= 0 || fat <= 0) {
    alert("Wszystkie wartości muszą być dodatnie!");
    return;
  }

  // Wysłanie zaktualizowanych danych na serwer
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState === 4 && this.status === 200) {
      alert("Produkt został zaktualizowany!");
      // Ukryj formularz edycji
      document.getElementById('editProductForm').style.display = 'none';
      // Odśwież tabelę
      getAttendanceListTable('tableAttendanceListId');
    }
  };

  xhttp.open("POST", "editProduct", true);
  xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  xhttp.send("id=" + productId + "&name=" + name + "&protein=" + protein + "&carb=" + carb + "&fat=" + fat);
}

// Funkcja anulowania edycji
function cancelEdit() {
  document.getElementById('editProductForm').style.display = 'none';
}


function loadProductOptions() {
  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState === 4 && this.status === 200) {
      var products = JSON.parse(this.responseText);
      var productSelect = document.getElementById('productSelect');
      productSelect.innerHTML = ""; // Czyść poprzednie dane

      products.forEach(function(product, index) {
        var option = document.createElement('option');
        option.value = index; // Id produktu jako wartość
        option.textContent = product.name; // Nazwa produktu
        productSelect.appendChild(option);
      });
    }
  };

  xhttp.open("GET", "productList", true); // Endpoint do pobrania listy produktów
  xhttp.send();
}

function submitConsumedProduct(event) {
  event.preventDefault(); // Zapobiega przeładowaniu strony

  var productId = document.getElementById('productSelect').value;
  var grams = document.getElementById('productGrams').value;

  var xhttp = new XMLHttpRequest();
  xhttp.onreadystatechange = function() {
    if (this.readyState === 4 && this.status === 200) {
      // Opcjonalnie pokaż wynik agregacji
      document.getElementById('aggregationResult').textContent = this.responseText;
    }
  };

  xhttp.open("POST", "consumeProduct", true);
  xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
  xhttp.send("id=" + encodeURIComponent(productId) + "&grams=" + encodeURIComponent(grams));
}

function consumeProduct(productId) {
    var grams = prompt("Podaj ilość gram:");

    if (grams === null || isNaN(grams) || grams <= 0) {
        alert("Niepoprawna ilość gram");
        return;
    }

    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState === 4 && this.status === 200) {
            alert("Produkt został dodany do zjedzonych!");
        } else if (this.readyState === 4) {
            alert("Wystąpił błąd: " + this.status);
        }
    };

    xhttp.open("POST", "consumeProduct", true);
    xhttp.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
    xhttp.send("id=" + encodeURIComponent(productId) + "&grams=" + encodeURIComponent(grams));
}