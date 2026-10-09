
using UnityEngine;

public class EnemigoIA : Personaje
{
    public float direccion = -1f;

    private Animator anim;

    protected override void Awake()
    {
        base.Awake();
        anim = GetComponent<Animator>();
    }

    void Update()
    {
        rb.velocity = new Vector2(direccion * velocidad, rb.velocity.y);

        if (anim != null)
        {
            anim.SetBool("Caminando", Mathf.Abs(rb.velocity.x) > 0.1f);
        }
    }

    void OnCollisionEnter2D(Collision2D col)
    {
        if (col.gameObject.CompareTag("Pared") ||
            col.gameObject.CompareTag("Obstaculo"))
        {
            direccion *= -1;
            sr.flipX = !sr.flipX;
        }

        if (col.gameObject.CompareTag("Player"))
        {
            if (col.contacts[0].normal.y < 0)
            {
                RecibirDaño(1);
            }
            else
            {
                col.gameObject.GetComponent<Jugador>().RecibirDaño(1);
            }
        }
    }
}
