using UnityEngine;

public class ControlJugador : MonoBehaviour
{
    public float velocidadActual = 0f;
    public float velocidadMax = 5f;
    public float aceleracion = 10f;
    public float velocidadVertical = 0f;
    public float gravedad = -20f;
    public float tiempoMaxSalto = 0.2f;
    private float tiempoSaltoActual = 0f;
    private float tiempoAnterior;
    private Jugador jugador;
    void Awake(){
    jugador = GetComponent<Jugador>();
    tiempoAnterior = Time.time;
    }
    void Update()
    {
        float delta = Time.time - tiempoAnterior;
        tiempoAnterior = Time.time;
        float h = Input.GetAxis("Horizontal");
        velocidadActual += h * aceleracion * delta;
        velocidadActual = Mathf.Clamp(velocidadActual, -velocidadMax, velocidadMax);
        transform.position += new Vector3(velocidadActual * delta, 0, 0);

        if (Mathf.Abs(h) > 0.01f){
            Debug.Log("Movimiento horizontal: " + h);
        }
    }
    void FixedUpdate()
    {
    }
}