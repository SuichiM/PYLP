/* Initialize */
import api from './services.js'

const clearForm = () => {
  document.getElementById("nombre").value = "";
  document.getElementById("apellido").value = "";
  document.getElementById("fecha").value = "";
};

//Agrega un elemento a la collection User
const guardar = async function () {
  const userData = {
    first: document.getElementById("nombre").value,
    last: document.getElementById("apellido").value,
    born: document.getElementById("fecha").value,
  };

  try {
    const docRef = await api.create(userData);

    console.log("Document written with ID: ", docRef.id);
    clearForm();
  } catch (error) {
    console.error("Error adding document: ", error);
  }
};

//Actualizar registro
const editar = function (id, nombre, apellido, fecha) {
  document.getElementById("nombre").value = nombre;
  document.getElementById("apellido").value = apellido;
  document.getElementById("fecha").value = fecha;

  var boton = document.getElementById("boton");
  boton.innerHTML = "Editar";

  boton.onclick = async () => {
    const userData = {
      first: document.getElementById("nombre").value,
      last: document.getElementById("apellido").value,
      born: document.getElementById("fecha").value,
    };

    try {
      const updatedRec = await api.update(id, userData);

      console.log("Document successfully updated!", updatedRec);
      clearForm();
      boton.innerHTML = "Guardar";
      boton.onclick = guardar;
    } catch (error) {
      console.error("Error updating document: ", error);
    }
  };
}

const eliminar = async function(id) {
  try {
    await api.delet(id);
    console.log("Document successfully deleted!");
  } catch (error) {
    console.error("Error removing document: ", error);
  }
}

// funcion que carga la data en la tabla
const loadData = (data) => {
  const tabla = document.getElementById("tabla");
  tabla.innerHTML = "";

  data.forEach((doc) => {
    console.log(doc.data());
    const { first, last, born } = doc.data();
    tabla.innerHTML += `
            <tr>
              <th scope="row">${doc.id}</th>
              <td>${first}</td>
              <td>${last}</td>
              <td>${born}</td>
              <td><button class="btn btn-danger" onclick="showModalEliminar('${doc.id}')" data-toggle="modal" data-target="#modalConfirmEliminar">Eliminar</button></td>
              <td><button class="btn btn-warning" onclick="editar('${doc.id}','${first}','${last}','${born}')">Editar</button></td>
            </tr>
          `;
  });
};

const showModalEliminar = (id)=>{
  const msg = document.getElementById("mensajeEliminar");
  const btnEliminar = document.getElementById('btnEliminar');
  msg.innerHTML = `¿Seguro desea eliminar el registro con ID: <b>${id} </b>?`

  btnEliminar.onclick = ()=>{
    eliminar(id)
    const modalEliminar = $('#modalConfirmEliminar').modal('hide');
  }

}

api.suscribe(loadData);

window.guardar = guardar
window.editar = editar
window.eliminar = eliminar
window.showModalEliminar = showModalEliminar