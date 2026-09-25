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
    public float desaceleracion = 8f;
    public float gravedadCaida = -30f;
    public float tiempoCoyote = 0.1f;
    public float tiempoBufferSalto = 0.1f;
    private float coyoteTimer = 0f;
    private float bufferTimer = 0f;

    public float fuerzaSalto = 10f;

    public bool estaCaminando;
    public bool estaSaltando;
    public bool estaCayendo;
    void Awake(){
    jugador = GetComponent<Jugador>();
    tiempoAnterior = Time.time;
    }
    void Update(){
        float delta = Time.time - tiempoAnterior;
        tiempoAnterior = Time.time;

        float h = Input.GetAxis("Horizontal");
        velocidadActual += h * aceleracion * delta;
        velocidadActual = Mathf.Clamp(velocidadActual, -velocidadMax, velocidadMax);

        if (Mathf.Abs(h) > 0.01f){
            Debug.Log("Movimiento horizontal: " + h);
        }

        if (h == 0){
            if (velocidadActual > 0)
                velocidadActual -= desaceleracion * delta;
            else if (velocidadActual < 0)
                velocidadActual += desaceleracion * delta;

            if (Mathf.Abs(velocidadActual) < 0.1f)
                velocidadActual = 0;
        }

        if (jugador.enSuelo)
            coyoteTimer = tiempoCoyote;
        else
            coyoteTimer -= delta;

        if (Input.GetAxis("Jump") > 0)
            bufferTimer = tiempoBufferSalto;
        else
            bufferTimer -= delta;
        
        if (bufferTimer > 0 && coyoteTimer > 0){
            velocidadVertical = fuerzaSalto;
            jugador.enSuelo = false;
            bufferTimer = 0;
            coyoteTimer = 0;
            Debug.Log("Input Detectado: Tecla de Salto (Espacio)");
        }

        if (velocidadVertical < 0)
            velocidadVertical += gravedadCaida * delta;
        else
            velocidadVertical += gravedad * delta;
        
        transform.position += new Vector3(
            velocidadActual * delta,
            velocidadVertical * delta,
            0
        );
    }
    void FixedUpdate()
    {
    }
}