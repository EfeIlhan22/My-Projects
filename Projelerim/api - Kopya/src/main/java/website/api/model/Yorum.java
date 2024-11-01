package website.api.model;

import jakarta.persistence.Entity;
import jakarta.persistence.GeneratedValue;
import jakarta.persistence.GenerationType;
import jakarta.persistence.Id;
import lombok.AllArgsConstructor;
import lombok.Data;
import lombok.NoArgsConstructor;

@Data
@AllArgsConstructor
@NoArgsConstructor
@Entity
public class Yorum {
    @Id
    @GeneratedValue(strategy=GenerationType.IDENTITY)
    private int id;
    private String username;
    private String nefretsebebi;
    private String startTime;
    private String yorum;
    private int like_count;
    private String photo_data_path;

}
