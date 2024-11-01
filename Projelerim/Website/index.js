

let username;
let sebebi; 

document.getElementById("submit").onclick=function(){
    username=document.getElementById("Kullanıcı").value;
    document.getElementById("deneme").textContent= `Hello ${username}`;
}