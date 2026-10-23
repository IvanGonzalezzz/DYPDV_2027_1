using UnityEngine;

public class Jugador : Personaje{
    public bool enSuelo = false;
    protected override void Awake(){
        base.Awake();
        Debug.Log("Awake: Objeto Jugador cargado en memoria");
    }
    private void Start(){
        Debug.Log("Start: Iniciando el objeto Jugador antes del primer frame");
    }
    private void OnCollisionEnter2D(Collision2D col){
        Debug.Log("OnCollisionEnter2D: Colision con " + col.gameObject.name);
        if (col.gameObject.CompareTag("Suelo")){
            enSuelo = true;
        }
    }
    private void OnCollisionStay2D(Collision2D col){
        Debug.Log("OnCollisionStay2D: Manteniendo con " + col.gameObject.name);
    }
    private void OnCollisionExit2D(Collision2D col){
        if (col.gameObject.CompareTag("Suelo")){
            enSuelo = false;
        }
    }
}