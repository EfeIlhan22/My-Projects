document.getElementById("girdisForm").addEventListener("submit", function(event) {
    event.preventDefault(); // Formun varsayılan gönderimini engelle

    // Hoca verilerini topla
    const hocaData = {
        ad: document.getElementById("ad").value,
        sebebi: document.getElementById("sebebi").value,
        zaman: document.getElementById("zaman").value,
        comment: document.getElementById("comment").value
    };

    // Hoca API'sine POST isteği gönder
    fetch('/api/hoca/create', {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(hocaData)
    })
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            console.log('Başarılı:', data);
            alert("Hoca başarıyla eklendi!");
        })
        .catch(error => {
            console.error('Hata:', error);
            alert("Bir hata oluştu. Lütfen tekrar deneyin.");
        });
});

// Yorum ekleme
document.getElementById("yorumForm").addEventListener("submit", function(event) {
    event.preventDefault(); // Formun varsayılan gönderimini engelle

    // Yorum verilerini topla
    const yorumData = {
        yorum: document.getElementById("yorum").value
    };
    const hocaId = document.getElementById("hocaId").value;

    // Yorum API'sine POST isteği gönder
    fetch(`https://hocasavar-api-1.onrender.com/api/hoca/${hocaId}/yorumlar`, {
        method: 'POST',
        headers: {
            'Content-Type': 'application/json'
        },
        body: JSON.stringify(yorumData)
    })
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            console.log('Başarılı:', data);
            alert("Yorum başarıyla eklendi!");
        })
        .catch(error => {
            console.error('Hata:', error);
            alert("Bir hata oluştu. Lütfen tekrar deneyin.");
        });
});

// Yorumları alma
function getYorumlar() {
    const hocaId = document.getElementById("hocaId").value;

    fetch(`https://hocasavar-api-1.onrender.com/api/hoca/${hocaId}/yorumlar`)
        .then(response => {
            if (!response.ok) {
                throw new Error('Network response was not ok');
            }
            return response.json();
        })
        .then(data => {
            const yorumlarListesi = document.getElementById("yorumlarListesi");
            yorumlarListesi.innerHTML = ''; // Önceki yorumları temizle

            data.forEach(yorum => {
                const div = document.createElement("div");
                div.textContent = yorum.yorum; // Yorum metnini ekle
                yorumlarListesi.appendChild(div);
            });
        })
        .catch(error => {
            console.error('Hata:', error);
            alert("Yorumları getirirken bir hata oluştu.");
        });
}
