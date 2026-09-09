using UnityEngine;

public class ControlJugador : MonoBehaviour
{
    void Update()
    {
        float h = Input.GetAxis("Horizontal");
        if (Mathf.Abs(h) > 0.01f)
        {
            Debug.Log("Movimiento horizontal: " + h);
        }
        if (Input.GetButtonDown("Jump"))
        {
            Debug.Log("Input Detectado: Tecla de Salto (Espacio)");
        }
    }
    void FixedUpdate()
    {
    }
}