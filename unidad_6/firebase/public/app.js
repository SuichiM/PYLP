/* Initialize */
import api from "./services.js";

const clearForm = () => {
  document.getElementById("nombre").value = "";
  document.getElementById("apellido").value = "";
  document.getElementById("fecha").value = "";
};

/**
 * showWarning: muestra un alert en pantalla
 * @param {*} type: tipo de error -> error | warning 
 * @param {*} msg: msg que se le mostrará al usuario
 */
function showWarning(type, msg) {
  const box = document.getElementById("warning_msj");

  const alert_type = {
    error: 'danger',
    warning: 'warning'
  }

  const alert = `<div class="alert alert-${alert_type[type]} alert-dismissible fade show" role="alert">
    <strong>${type}</strong> ${msg}
    <button type="button" class="close" data-dismiss="alert" aria-label="Close">
      <span aria-hidden="true">&times;</span>
    </button>
  </div>`;

  box.innerHTML = alert;
}

/**
 * validarDatos: valida los datos obligatorios de una persona  
 * y llama al showWarning en caso de que haya errores 
 * @returns Boolean
 * @param {*} persona 
 */
function validarDatos(persona) {
  let { first, last, born } = persona;

  if ((first = null || first.length == 0 || /^\s+$/.test(first))) {
    showWarning("error", "El campo nombre debe tener un valor");
    return false;
  }

  if ((last = null || last.length == 0 || /^\s+$/.test(last))) {
    showWarning("error", "El campo apellido debe tener un valor");
    return false;
  }

  if ((born = null || born.length == 0 ))
    showWarning("warning", "El campo fecha viajo vacio");
    

  return true;
}

/**
 * guardar: Toma los datos del formulario 
 *  e intenta crear un nuevo registro en firebase
 */
const guardar = async function () {
  const userData = {
    first: document.getElementById("nombre").value,
    last: document.getElementById("apellido").value,
    born: document.getElementById("fecha").value,
  };

  try {
    const isValid = validarDatos(userData);
    if (!isValid) return;

    const docRef = await api.create(userData);

    console.log("Document written with ID: ", docRef.id);
    clearForm();

  } catch (error) {
    console.error("Error adding document: ", error);
  }

  /** 
  EQUIVALENTE AL TRY CATCH CON PROMISES 
    const isValid = validarDatos(userData);
    if (!isValid) return;

    api.create(userData)
    .then((docRef)=>{
      console.log("Document written with ID: ", docRef.id);
      clearForm(); 
    })
    .catch((error)=>{
      console.error("Error adding document: ", error);
    }) 
  */
};

/**
 * editar: carga los valores en el formulario, 
 *  modifica la etiqueta del boton a "Editar"
 *  y modifica la funcion onClick por la de modificar
 * @param {*} id: id del documento que se desea modificar
 * @param {*} nombre    
 * @param {*} apellido
 * @param {*} fecha 
 */
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
      const isValid = validarDatos(userData);
      if (!isValid) return;

      const updatedRec = await api.update(id, userData);

      console.log("Document successfully updated!", updatedRec);
      clearForm();
      boton.innerHTML = "Guardar";
      boton.onclick = guardar;
    } catch (error) {
      console.error("Error updating document: ", error);
    }
  };
};

/**
 * eliminar: intenta eliminar el documento de firebase
 * @param {*} id 
 */
const eliminar = async function (id) {
  try {
    await api.delet(id);
    console.log("Document successfully deleted!");
  } catch (error) {
    console.error("Error removing document: ", error);
  }
};

/**
 * loadData: funcion que se llama cuando se realizan cambios en firebase
 *  data son los datos que manda firebase
 *  esta funcion toma la tabla del html y actualiza los datos con data
 * @param {*} data 
 */
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

/**
 * showModalEliminar: muestra el mensaje de confirmacion para eliminar
 *  y define la funcion del boton confirmar del modal
 * @param {*} id 
 */
const showModalEliminar = (id) => {
  const msg = document.getElementById("mensajeEliminar");
  const btnEliminar = document.getElementById("btnEliminar");
  msg.innerHTML = `¿Seguro desea eliminar el registro con ID: <b>${id} </b>?`;

  btnEliminar.onclick = () => {
    eliminar(id);
    const modalEliminar = $("#modalConfirmEliminar").modal("hide");
  };
};

/** MAIN */

/**
 * api.suscribe, va a quedar escuchando la coleccion 'users' 
 * y cada vez que haya cambios, va a llamar a loadData
 */
api.suscribe(loadData, "users");

/* 
 * para poder usar el import del services en este archivo, 
 * es necesario definirlo como module cuando cargamos en el html  
 * por eso TODOS las funciones llamadas desde el HTML deben asociarse al 
 * objeto window para que funcionen
 */
window.guardar = guardar;
window.editar = editar;
window.eliminar = eliminar;
window.showModalEliminar = showModalEliminar;
